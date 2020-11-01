
/** Copyright (C) 2023 briand (https://github.com/briand-hub)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#if defined(__linux__) | defined(_WIN32)

    #include "BriandInclude.hxx"

	const char *esp_err_to_name(esp_err_t code) {
		return "UNDEFINED ON LINUX PLATFORM";
	}

	unique_ptr<map<string, esp_log_level_t>> LOG_LEVELS_MAP;
	
	void esp_log_level_set(const char* tag, esp_log_level_t level) {
		// If wildcard, all to level.
		if (strcmp(tag, "*") == 0) {
			for (auto it = LOG_LEVELS_MAP->begin(); it != LOG_LEVELS_MAP->end(); ++it) {
				it->second = level;
			}
		}
		else {
			(*LOG_LEVELS_MAP.get())[string(tag)] = level;
		}
	}

	esp_log_level_t esp_log_level_get(const char* tag) {
		auto it = LOG_LEVELS_MAP->find(string(tag));
		
		if (it == LOG_LEVELS_MAP->end()) {
			// Create
			(*LOG_LEVELS_MAP.get())[string(tag)] = ESP_LOG_NONE;
		}
		
		return (*LOG_LEVELS_MAP.get())[string(tag)];
	}

	void ESP_ERROR_CHECK(esp_err_t e) { /* do nothing */ }

	void heap_caps_get_info(multi_heap_info_t* info, uint32_t caps) {
		bzero(info, sizeof(info));
		// Standard ESP 320KB
		// default return 0 for free bytes
		info->total_free_bytes = 0;
		info->total_allocated_bytes = 0;
	}

	void rtc_clk_cpu_freq_get_config(rtc_cpu_freq_config_t* info) { info->freq_mhz = 240; }
	void rtc_clk_cpu_freq_mhz_to_config(uint32_t mhz, rtc_cpu_freq_config_t* out) { out->freq_mhz = mhz; }
	void rtc_clk_cpu_freq_set_config(rtc_cpu_freq_config_t* info) { /* do nothing */ }

	size_t heap_caps_get_largest_free_block(uint32_t caps) { return 0; }

	BriandIDFPortingTaskHandle::BriandIDFPortingTaskHandle(const std::thread::native_handle_type& h, const char* name, const std::thread::id& tid) {
		this->handle = h;
		this->name = string(name);
		this->thread_id = tid;
		this->toBeKilled = false;
	}

	BriandIDFPortingTaskHandle::~BriandIDFPortingTaskHandle() {
		if (esp_log_level_get("ESPLinuxPorting") != ESP_LOG_NONE) cout << "BriandIDFPortingTaskHandle: " << this->name << " destroyed." << endl;
	}

	unique_ptr<vector<TaskHandle_t>> BRIAND_TASK_POOL = nullptr;

	TickType_t CTRL_C_MAX_WAIT = 0; // this is useful max waiting time before killing thread (see main()) 

	void vTaskDelay(TickType_t delay) { 
		if (CTRL_C_MAX_WAIT < delay) CTRL_C_MAX_WAIT = delay;
		std::this_thread::sleep_for( std::chrono::milliseconds(delay) ); 
	}

	uint64_t esp_timer_get_time() { 
		// Should return microseconds!
		auto clockPrecision = std::chrono::system_clock::now().time_since_epoch();
		auto micros = std::chrono::duration_cast<std::chrono::microseconds>(clockPrecision);
		return micros.count(); 
	}

	BaseType_t xTaskCreate(
			TaskFunction_t pvTaskCode,
			const char * const pcName,
			const uint32_t usStackDepth,
			void * const pvParameters,
			UBaseType_t uxPriority,
			TaskHandle_t * const pvCreatedTask)
	{
		// do not worry for prioriry and task depth now...

		std::thread t(pvTaskCode, pvParameters);
		TaskHandle_t tHandle = new BriandIDFPortingTaskHandle(t.native_handle(), pcName, t.get_id());

		if (pvCreatedTask != NULL) {
			*pvCreatedTask = tHandle;
		}

		// Add the task to pool BEFORE detach() otherwise native id is lost
		BRIAND_TASK_POOL->push_back( tHandle );

		t.detach(); // this will create daemon-like threads

		return static_cast<BaseType_t>(BRIAND_TASK_POOL->size()-1); // task index
	}

	void vTaskDelete(TaskHandle_t handle) {
		std::thread::id idToKill;

		if (handle == NULL || handle == nullptr) {
			// Terminate this
			idToKill = std::this_thread::get_id();
		}
		else {
			idToKill = handle->thread_id;
		}

		if (BRIAND_TASK_POOL != nullptr) {
			for (int i = 0; i<BRIAND_TASK_POOL->size(); i++) {
				if (BRIAND_TASK_POOL->at(i)->thread_id == idToKill) {
					BRIAND_TASK_POOL->at(i)->toBeKilled = true;
					break;
				}
			}