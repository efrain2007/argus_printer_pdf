
import 'argus_printer_pdf_platform_interface.dart';

class ArgusPrinterPdf {
  Future<String?> getPlatformVersion() {
    return ArgusPrinterPdfPlatform.instance.getPlatformVersion();
  }
}
