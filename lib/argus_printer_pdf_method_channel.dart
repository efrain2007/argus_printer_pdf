import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'argus_printer_pdf_platform_interface.dart';

/// An implementation of [ArgusPrinterPdfPlatform] that uses method channels.
class MethodChannelArgusPrinterPdf extends ArgusPrinterPdfPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('argus_printer_pdf');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }
}
