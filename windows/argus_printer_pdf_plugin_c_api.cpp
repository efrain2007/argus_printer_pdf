#include "include/argus_printer_pdf/argus_printer_pdf_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "argus_printer_pdf_plugin.h"

void ArgusPrinterPdfPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  argus_printer_pdf::ArgusPrinterPdfPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
