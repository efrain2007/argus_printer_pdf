

// This must be included before many other Windows headers.
#ifndef UNICODE
#define UNICODE
#define UNICODE_WAS_UNDEFINED
#endif

#include <Windows.h>

#ifdef UNICODE_WAS_UNDEFINED
#undef UNICODE
#endif

// For getPlatformVersion; remove unless needed for your plugin implementation.




#include <map>
#include <memory>
#include <sstream>
#include "pdfium/include/fpdfview.h"
#include <fstream>
#include <iostream>
using namespace std;

namespace {

	

	std::string printPdfFile(std::string fileprint, std::string printerName, std::string pageNumber, std::string orientation) {
		wchar_t* wString = new wchar_t[4096];
		MultiByteToWideChar(CP_ACP, 0, printerName.c_str(), -1, wString, 4096);
		FPDF_LIBRARY_CONFIG config;
		config.version = 2;
		config.m_pUserFontPaths = NULL;
		config.m_pIsolate = NULL;
		config.m_v8EmbedderSlot = 0;
		double page_width, page_height;
		int size_x, size_y, logpixelsx, logpixelsy, _orientation;
		_orientation = orientation == "LANDSCAPE_PAGE" ? 1 : 0;
		FPDF_InitLibraryWithConfig(&config);

		FPDF_DOCUMENT doc;
		ifstream ifile;
		ifile.open(fileprint);
		if (ifile) {
			//cout << "file exists\n";
		}
		else {
			//cout << "file doesn't exist";
			// fileprint.append(" file doesn't exist")
			return "-1";
		}
		try
		{
			doc = FPDF_LoadDocument(fileprint.c_str(), NULL);
		}
		catch (const std::exception&)
		{
			//fileprint.append(" DOC ERROR")
			return "-2";
		}

		if (doc == NULL) {
			unsigned long err = FPDF_GetLastError();
			fprintf(stderr, "Load pdf docs unsuccessful: ");
			switch (err) {
			case FPDF_ERR_SUCCESS:
				fprintf(stderr, "Success");
				break;
			case FPDF_ERR_UNKNOWN:
				fprintf(stderr, "Unknown error");
				break;
			case FPDF_ERR_FILE:
				fprintf(stderr, "File not found or could not be opened");
				break;
			case FPDF_ERR_FORMAT:
				fprintf(stderr, "File not in PDF format or corrupted");
				break;
			case FPDF_ERR_PASSWORD:
				fprintf(stderr, "Password required or incorrect password");
				break;
			case FPDF_ERR_SECURITY:
				fprintf(stderr, "Unsupported security scheme");
				break;
			case FPDF_ERR_PAGE:
				fprintf(stderr, "Page not found or content error");
				break;
			default:
				fprintf(stderr, "Unknown error %ld", err);
			}
			fprintf(stderr, ".\n");
			// fileprint.append(" DOC NULL")
			return "-3";
		}

		HDC hDC = CreateDC(L"WINSPOOL", wString, NULL, NULL);

		if (hDC == NULL) {
			// printerName.append(" HDC NULL")
			return "-4";
		}
		DOCINFO doc_info = { sizeof(DOCINFO) };
		StartDoc(hDC, &doc_info);
		StartPage(hDC);

		int pageCount = FPDF_GetPageCount(doc);
		if (pageNumber == "ALL_PAGES") {
			for (int i = 0; i < pageCount; i++) {
				FPDF_PAGE pdf_page = FPDF_LoadPage(doc, i);
				if (pdf_page == NULL) return "-5";
				page_width = FPDF_GetPageWidth(pdf_page);;
				page_height = FPDF_GetPageHeight(pdf_page);
				logpixelsx = GetDeviceCaps(hDC, LOGPIXELSX);
				logpixelsy = GetDeviceCaps(hDC, LOGPIXELSY);
				size_x = (int)page_width / 60 * logpixelsx;
				size_y = (int)page_height / 60 * logpixelsy;
				//int start_y = i * size_y;
				FPDF_RenderPage(hDC, pdf_page, 0, 0, size_x, size_y, _orientation, 0);
				FPDF_ClosePage(pdf_page);
			}
		}
		else {
			FPDF_PAGE pdf_page = FPDF_LoadPage(doc, std::stoi(pageNumber.c_str()));
			if (pdf_page == NULL) return "-5";
			page_width = FPDF_GetPageWidth(pdf_page);;
			page_height = FPDF_GetPageHeight(pdf_page);
			logpixelsx = GetDeviceCaps(hDC, LOGPIXELSX);
			logpixelsy = GetDeviceCaps(hDC, LOGPIXELSY);
			size_x = (int)page_width / 60 * logpixelsx;
			size_y = (int)page_height / 60 * logpixelsy;
			FPDF_RenderPage(hDC, pdf_page, 0, 0, size_x, size_y, _orientation, 0);
			FPDF_ClosePage(pdf_page);
		}

		EndPage(hDC);
		EndDoc(hDC);
		DeleteDC(hDC);
		FPDF_CloseDocument(doc);
		wprintf(L"PDF Success\n");

		FPDF_DestroyLibrary();
		return "1";

	}

	std::string PrinterList() {
		std::string listPrinter = "";
		PRINTER_INFO_2* list;
		DWORD            cnt = 0;
		DWORD            sz = 0;
		DWORD Level = 2;
		int            i;
		int            sl;

		EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, NULL, Level, NULL, 0, &sz, &cnt);

		if ((list = (PRINTER_INFO_2*)malloc(sz)) == 0)    return 0;

		if (!EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, NULL, Level, (LPBYTE)list, sz, &sz, &cnt))
		{
			free(list);
			return 0;
		}

		for (i = 0, sl = 0; i < (int)cnt; i++)
		{

			std::string strTo;
			LPWSTR  printerName = list[i].pPrinterName;
			char* p = 0;
			int bsz;
			UINT codepage = CP_ACP;
			bsz = WideCharToMultiByte(codepage, 0, printerName, -1, 0, 0, 0, 0);
			if (bsz > 0) {
				p = new char[bsz];
				int rc = WideCharToMultiByte(codepage, 0, printerName, -1, p, bsz, 0, 0);
				if (rc != 0) {
					p[bsz - 1] = 0;
					strTo = p;
				}
			}
			delete[] p;
			if (listPrinter == "") {
				listPrinter.append(strTo);
			}
			else {
				listPrinter.append(";").append(strTo);
			}

		}

		//cout << "listPrinter\n";
	wcout << listPrinter.c_str() << endl;

		return listPrinter;
	}



	

}  // namespace

 int main()
{
  PrinterList();
  cout << "Hello world" << endl;
}

