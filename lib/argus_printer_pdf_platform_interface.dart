import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'argus_printer_pdf_method_channel.dart';

abstract class ArgusPrinterPdfPlatform extends PlatformInterface {
  /// Constructs a ArgusPrinterPdfPlatform.
  ArgusPrinterPdfPlatform() : super(token: _token);

  static final Object _token = Object();

  static ArgusPrinterPdfPlatform _instance = MethodChannelArgusPrinterPdf();

  /// The default instance of [ArgusPrinterPdfPlatform] to use.
  ///
  /// Defaults to [MethodChannelArgusPrinterPdf].
  static ArgusPrinterPdfPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [ArgusPrinterPdfPlatform] when
  /// they register themselves.
  static set instance(ArgusPrinterPdfPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}
