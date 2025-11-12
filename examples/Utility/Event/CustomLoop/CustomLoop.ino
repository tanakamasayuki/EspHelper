#include <EspHelperEvent.h>

ESP_EVENT_DECLARE_BASE(SENSOR_EVENT_BASE);
ESP_EVENT_DEFINE_BASE(SENSOR_EVENT_BASE);

enum : int32_t
{
  SENSOR_EVENT_SAMPLE = 0,
};

struct SensorSample
{
  uint32_t sequence;
  float value;
};

EspHelper::EventLoop sensorLoop;
uint32_t sequence = 0;

void onSensorSample(void *, esp_event_base_t, int32_t, void *event_data)
{
  const SensorSample *sample = static_cast<const SensorSample *>(event_data);
  Serial.printf("[custom loop] seq=%lu value=%.3f\n", sample->sequence, sample->value);
}

void setup()
{
  Serial.begin(115200);

  esp_event_loop_args_t args = {
      .queue_size = 8,
      .task_name = "sensor_evt",
      .task_priority = 4,
      .task_stack_size = 4096,
      .task_core_id = APP_CPU_NUM,
  };

  if (!sensorLoop.createCustom(args))
  {
    Serial.println("Failed to create custom event loop");
    while (true)
    {
      delay(1000);
    }
  }

  sensorLoop.registerHandler(SENSOR_EVENT_BASE, SENSOR_EVENT_SAMPLE, &onSensorSample);
}

void loop()
{
  SensorSample sample{};
  sample.sequence = ++sequence;
  sample.value = static_cast<float>(esp_random() % 1000) / 1000.0f;
  sensorLoop.post(SENSOR_EVENT_BASE, SENSOR_EVENT_SAMPLE, &sample, sizeof(sample));
  delay(500);
}
