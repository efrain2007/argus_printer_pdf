import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:argus_printer_pdf/argus_printer_pdf_method_channel.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  MethodChannelArgusPrinterPdf platform = MethodChannelArgusPrinterPdf();
  const MethodChannel channel = MethodChannel('argus_printer_pdf');

  setUp(() {
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger.setMockMethodCallHandler(
      channel,
      (MethodCall methodCall) async {
        return '42';
      },
    );
  });

  tearDown(() {
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger.setMockMethodCallHandler(channel, null);
  });

  test('getPlatformVersion', () async {
    expect(await platform.getPlatformVersion(), '42');
  });
}
