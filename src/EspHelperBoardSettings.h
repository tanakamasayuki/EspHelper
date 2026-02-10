#pragma once

#include <Arduino.h>
#include <esp_partition.h>
#include <soc/soc_caps.h>
#include <string.h>
#include "sdkconfig.h"

class EspHelperBoardSettings
{
public:
    static void dump()
    {
        Serial.println();
        Serial.println("=== ESP32 Arduino Board Settings ===");

        // Upload/USB related (compile-time if available)
        printIfUsbAvailable("USB CDC On Boot", resolveCdcOnBootLabel());
        printIfAvailable("CPU Frequency", resolveCpuFreqLabel());
        printIfAvailable("Core Debug Level", resolveDebugLevelLabel());
        printIfUsbAvailable("USB DFU On Boot", resolveDfuOnBootLabel());
        printIfAvailable("Events Run On", resolveEventsCoreLabel());
        printIfAvailable("Flash Mode", resolveFlashModeLabel());
        printIfAvailable("Flash Size", resolveFlashSizeLabel());
        printIfAvailable("Arduino Runs On", resolveLoopCoreLabel());
        printIfUsbAvailable("USB Firmware MSC On Boot", resolveMscOnBootLabel());
        printIfAvailable("PSRAM", resolvePsramLabel());
        printIfAvailable("Partition Scheme", resolvePartitionSchemeLabel());
        printIfUsbAvailable("USB Mode", resolveUsbModeLabel());

        Serial.println("=== end ===");
    }

private:
    static const char *resolveUsbModeLabel()
    {
#ifdef ARDUINO_USB_MODE
        return ARDUINO_USB_MODE ? "Hardware CDC and JTAG" : "USB-OTG (TinyUSB)";
#else
        return "(not available at runtime)";
#endif
    }

    static const char *resolveCdcOnBootLabel()
    {
#ifdef ARDUINO_USB_CDC_ON_BOOT
        return ARDUINO_USB_CDC_ON_BOOT ? "Enabled" : "Disabled";
#else
        return "(not available at runtime)";
#endif
    }

    static const char *resolveMscOnBootLabel()
    {
#ifdef ARDUINO_USB_MSC_ON_BOOT
        return ARDUINO_USB_MSC_ON_BOOT ? "Enabled (Requires USB-OTG Mode)" : "Disabled";
#else
        return "(not available at runtime)";
#endif
    }

    static const char *resolveDfuOnBootLabel()
    {
#ifdef ARDUINO_USB_DFU_ON_BOOT
        return ARDUINO_USB_DFU_ON_BOOT ? "Enabled (Requires USB-OTG Mode)" : "Disabled";
#else
        return "(not available at runtime)";
#endif
    }

    static const char *resolveCpuFreqLabel()
    {
        switch (F_CPU)
        {
        case 240000000L:
            return "240MHz (WiFi)";
        case 160000000L:
            return "160MHz (WiFi)";
        case 80000000L:
            return "80MHz (WiFi)";
        case 40000000L:
            return "40MHz";
        case 20000000L:
            return "20MHz";
        case 10000000L:
            return "10MHz";
        default:
            return "(unknown)";
        }
    }

    static const char *resolveFlashModeLabel()
    {
        static char mode_buf[20];
        const char *mode = nullptr;
        switch (ESP.getFlashChipMode())
        {
        case FM_QIO:
            mode = "QIO";
            break;
        case FM_DIO:
            mode = "DIO";
            break;
        case FM_DOUT:
            mode = "OPI";
            break;
        default:
            mode = "UNKNOWN";
            break;
        }

        const char *freq = resolveFlashFreqLabel();
        if (!freq || strcmp(freq, "(unknown)") == 0)
        {
            snprintf(mode_buf, sizeof(mode_buf), "%s", mode);
        }
        else
        {
            snprintf(mode_buf, sizeof(mode_buf), "%s %s", mode, freq);
        }
        return mode_buf;
    }

    static const char *resolveFlashFreqLabel()
    {
        unsigned long hz = ESP.getFlashChipSpeed();
        if (hz == 120000000UL)
        {
            return "120MHz";
        }
        if (hz == 80000000UL)
        {
            return "80MHz";
        }
        if (hz == 60000000UL)
        {
            return "60MHz";
        }
        if (hz == 40000000UL)
        {
            return "40MHz";
        }
        if (hz == 30000000UL)
        {
            return "30MHz";
        }
        return "(unknown)";
    }

    static const char *resolveFlashSizeLabel()
    {
        unsigned long size = ESP.getFlashChipSize();
        if (size == 8UL * 1024UL * 1024UL)
        {
            return "8MB (64Mb)";
        }
        if (size == 4UL * 1024UL * 1024UL)
        {
            return "4MB (32Mb)";
        }
        if (size == 2UL * 1024UL * 1024UL)
        {
            return "2MB (16Mb)";
        }
        return "(unknown)";
    }

    static const char *resolvePartitionSchemeLabel()
    {
        return buildPartitionSummary();
    }

    static const char *buildPartitionSummary()
    {
        static char summary[320];
        size_t app_count = 0;
        size_t app_total = 0;
        size_t nvs_total = 0;
        size_t otadata_total = 0;
        size_t spiffs_total = 0;
        size_t fatfs_total = 0;

        esp_partition_iterator_t it = esp_partition_find(ESP_PARTITION_TYPE_APP,
                                                         ESP_PARTITION_SUBTYPE_ANY,
                                                         nullptr);
        while (it != nullptr)
        {
            const esp_partition_t *p = esp_partition_get(it);
            if (p)
            {
                app_count++;
                app_total += p->size;
            }
            it = esp_partition_next(it);
        }
        if (it)
        {
            esp_partition_iterator_release(it);
        }

        it = esp_partition_find(ESP_PARTITION_TYPE_DATA,
                                ESP_PARTITION_SUBTYPE_ANY,
                                nullptr);
        while (it != nullptr)
        {
            const esp_partition_t *p = esp_partition_get(it);
            if (p)
            {
                switch (p->subtype)
                {
                case ESP_PARTITION_SUBTYPE_DATA_NVS:
                    nvs_total += p->size;
                    break;
                case ESP_PARTITION_SUBTYPE_DATA_OTA:
                    otadata_total += p->size;
                    break;
                case ESP_PARTITION_SUBTYPE_DATA_SPIFFS:
                    spiffs_total += p->size;
                    break;
                case ESP_PARTITION_SUBTYPE_DATA_FAT:
                    fatfs_total += p->size;
                    break;
                default:
                    break;
                }
            }
            it = esp_partition_next(it);
        }
        if (it)
        {
            esp_partition_iterator_release(it);
        }

        unsigned long flash_bytes = ESP.getFlashChipSize();
        unsigned long flash_kb = flash_bytes / 1024UL;
        unsigned long app_kb = app_total / 1024UL;
        unsigned long spiffs_kb = spiffs_total / 1024UL;
        unsigned long fatfs_kb = fatfs_total / 1024UL;
        unsigned long nvs_kb = nvs_total / 1024UL;
        unsigned long otadata_kb = otadata_total / 1024UL;

        char flash_buf[16];
        char app_buf[16];
        char app_each_buf[16];
        char spiffs_buf[16];
        char fatfs_buf[16];
        char nvs_buf[16];
        char otadata_buf[16];
        char parts_buf[200];
        parts_buf[0] = '\0';

        formatSize(flash_buf, sizeof(flash_buf), flash_kb, true);
        formatSize(app_buf, sizeof(app_buf), app_kb, false);
        formatSize(spiffs_buf, sizeof(spiffs_buf), spiffs_kb, false);
        formatSize(fatfs_buf, sizeof(fatfs_buf), fatfs_kb, false);
        formatSize(nvs_buf, sizeof(nvs_buf), nvs_kb, false);
        formatSize(otadata_buf, sizeof(otadata_buf), otadata_kb, false);
        if (app_count > 0)
        {
            unsigned long app_each_kb = app_kb / app_count;
            formatSize(app_each_buf, sizeof(app_each_buf), app_each_kb, false);
        }
        else
        {
            app_each_buf[0] = '\0';
        }

        parts_buf[0] = '\0';
        if (app_count > 1)
        {
            char app_item[32];
            snprintf(app_item, sizeof(app_item), "%s x%lu", app_each_buf,
                     static_cast<unsigned long>(app_count));
            appendExtraSize(parts_buf, sizeof(parts_buf), "APP", app_item);
        }
        else if (app_kb > 0)
        {
            appendExtraSize(parts_buf, sizeof(parts_buf), "APP", app_buf);
        }

        if (spiffs_kb > 0)
        {
            appendExtraSize(parts_buf, sizeof(parts_buf), "SPIFFS", spiffs_buf);
        }
        if (fatfs_kb > 0)
        {
            appendExtraSize(parts_buf, sizeof(parts_buf), "FATFS", fatfs_buf);
        }

        char extras_buf[120];
        extras_buf[0] = '\0';
        if (nvs_kb > 0)
        {
            appendExtraSize(extras_buf, sizeof(extras_buf), "NVS", nvs_buf);
        }
        if (otadata_kb > 0)
        {
            appendExtraSize(extras_buf, sizeof(extras_buf), "OTADATA", otadata_buf);
        }

        summary[0] = '\0';
        appendText(summary, sizeof(summary), flash_buf);
        appendText(summary, sizeof(summary), " (");
        appendText(summary, sizeof(summary), parts_buf);
        if (extras_buf[0] != '\0')
        {
            appendText(summary, sizeof(summary), ", ");
            appendText(summary, sizeof(summary), extras_buf);
        }
        appendText(summary, sizeof(summary), ")");
        return summary;
    }

    static void formatSize(char *out, size_t out_size, unsigned long kb,
                           bool always_mb)
    {
        if (!out || out_size == 0)
        {
            return;
        }
        if (!always_mb && kb < 1024UL)
        {
            snprintf(out, out_size, "%luKB", kb);
            return;
        }
        unsigned long mb10 = (kb * 10UL + 512UL) / 1024UL;
        unsigned long whole = mb10 / 10UL;
        unsigned long frac = mb10 % 10UL;
        if (frac == 0)
        {
            snprintf(out, out_size, "%luMB", whole);
        }
        else
        {
            snprintf(out, out_size, "%lu.%luMB", whole, frac);
        }
    }

    static void appendExtra(char *out, size_t out_size, const char *value)
    {
        if (!out || out_size == 0 || !value || value[0] == '\0')
        {
            return;
        }
        if (out[0] != '\0')
        {
            strncat(out, ", ", out_size - strlen(out) - 1);
        }
        strncat(out, value, out_size - strlen(out) - 1);
    }

    static void appendExtraSize(char *out, size_t out_size, const char *label,
                                const char *value)
    {
        if (!out || out_size == 0 || !label || !value || value[0] == '\0')
        {
            return;
        }
        if (out[0] != '\0')
        {
            strncat(out, ", ", out_size - strlen(out) - 1);
        }
        strncat(out, label, out_size - strlen(out) - 1);
        strncat(out, " ", out_size - strlen(out) - 1);
        strncat(out, value, out_size - strlen(out) - 1);
    }

    static void appendText(char *out, size_t out_size, const char *value)
    {
        if (!out || out_size == 0 || !value || value[0] == '\0')
        {
            return;
        }
        strncat(out, value, out_size - strlen(out) - 1);
    }

    static const char *resolveDebugLevelLabel()
    {
#ifdef CORE_DEBUG_LEVEL
        switch (CORE_DEBUG_LEVEL)
        {
        case 0:
            return "None";
        case 1:
            return "Error";
        case 2:
            return "Warn";
        case 3:
            return "Info";
        case 4:
            return "Debug";
        case 5:
            return "Verbose";
        default:
            return "(unknown)";
        }
#else
        return "(not available at runtime)";
#endif
    }

    static const char *resolvePsramLabel()
    {
#ifdef BOARD_HAS_PSRAM
        static char psram_buf[24];
        const char *psram_mode = nullptr;
#if defined(CONFIG_SPIRAM_MODE_OCT)
        psram_mode = "OPI";
#elif defined(CONFIG_SPIRAM_MODE_QUAD)
        psram_mode = "QSPI";
#endif
        if (psram_mode)
        {
            snprintf(psram_buf, sizeof(psram_buf), "Enabled(%s)", psram_mode);
            return psram_buf;
        }
        return "Enabled";
#else
        return "Disabled";
#endif
    }

    static const char *resolveLoopCoreLabel()
    {
#ifdef ARDUINO_RUNNING_CORE
        return ARDUINO_RUNNING_CORE ? "Core 1" : "Core 0";
#else
        return "(not available at runtime)";
#endif
    }

    static const char *resolveEventsCoreLabel()
    {
#ifdef ARDUINO_EVENT_RUNNING_CORE
        return ARDUINO_EVENT_RUNNING_CORE ? "Core 1" : "Core 0";
#else
        return "(not available at runtime)";
#endif
    }

    static void printStr(const char *label, const char *v)
    {
        Serial.printf("%-40s: %s\n", label, v ? v : "(null)");
    }

    static bool usbSupported()
    {
#if defined(SOC_USB_OTG_SUPPORTED) && SOC_USB_OTG_SUPPORTED
        return true;
#elif defined(SOC_USB_SERIAL_JTAG_SUPPORTED) && SOC_USB_SERIAL_JTAG_SUPPORTED
        return true;
#else
        return false;
#endif
    }

    static void printIfAvailable(const char *label, const char *v)
    {
        if (!v || strcmp(v, "(not available at runtime)") == 0)
        {
            return;
        }
        printStr(label, v);
    }

    static void printIfUsbAvailable(const char *label, const char *v)
    {
        if (!usbSupported())
        {
            return;
        }
        printIfAvailable(label, v);
    }
};
