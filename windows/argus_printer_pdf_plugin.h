#ifndef FLUTTER_PLUGIN_ARGUS_PRINTER_PDF_PLUGIN_H_
#define FLUTTER_PLUGIN_ARGUS_PRINTER_PDF_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace argus_printer_pdf {

class ArgusPrinterPdfPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  ArgusPrinterPdfPlugin();

  virtual ~ArgusPrinterPdfPlugin();

  // Disallow copy and assign.
  ArgusPrinterPdfPlugin(const ArgusPrinterPdfPlugin&) = delete;
  ArgusPrinterPdfPlugin& operator=(const ArgusPrinterPdfPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace argus_printer_pdf

#endif  // FLUTTER_PLUGIN_ARGUS_PRINTER_PDF_PLUGIN_H_
