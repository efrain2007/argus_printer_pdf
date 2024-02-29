import 'package:flutter_test/flutter_test.dart';
import 'package:argus_printer_pdf/argus_printer_pdf.dart';
import 'package:argus_printer_pdf/argus_printer_pdf_platform_interface.dart';
import 'package:argus_printer_pdf/argus_printer_pdf_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockArgusPrinterPdfPlatform
    with MockPlatformInterfaceMixin
    implements ArgusPrinterPdfPlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final ArgusPrinterPdfPlatform initialPlatform = ArgusPrinterPdfPlatform.instance;

  test('$MethodChannelArgusPrinterPdf is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelArgusPrinterPdf>());
  });

  test('getPlatformVersion', () async {
    ArgusPrinterPdf argusPrinterPdfPlugin = ArgusPrinterPdf();
    MockArgusPrinterPdfPlatform fakePlatform = MockArgusPrinterPdfPlatform();
    ArgusPrinterPdfPlatform.instance = fakePlatform;

    expect(await argusPrinterPdfPlugin.getPlatformVersion(), '42');
  });
}
