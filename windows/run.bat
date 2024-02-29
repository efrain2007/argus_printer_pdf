PDF_LIBS="-lpdfium -lfpdfapi -lfxge -lfpdfdoc -lfxcrt -lfx_agg -lfxcodec -lfx_lpng -lfx_libopenjpeg -lfx_lcms2 -lfx_freetype -ljpeg -lfx_zlib -lfdrm -lpdfwindow -lbigint -lformfiller -ljavascript -lfxedit"
PDF_DIR=C:\Users\51925\Documents\flutter\argus_printer_pdf\windows\pdfium

g++ -o printer.exe windows_printing_plugin.cpp   -lstdc++  $PDF_DIR