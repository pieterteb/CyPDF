# CyPDF

PDF generation library used by [CyPress](https://github.com/quirijndubois/CyPress). Written in C. Also check out [CyDE](https://github.com/quirijndubois/CyDE).

This project uses the following PDF documentation:
* The ISO standard for PDF 2.0 which can be obtained for free as of April 5, 2023, at: https://www.pdfa-inc.org/product/iso-32000-2-pdf-2-0-bundle-sponsored-access/.
* The PDF 1.7 reference by Adobe which is open source: https://opensource.adobe.com/dc-acrobat-sdk-docs/pdfstandards/pdfreference1.7old.pdf. This file can also be found in the resources folder.


Current functionalities:
* Creation of pages of any (by PDF supported) size.
* Addition of simple graphical elements to specific pages. These are shapes constructed with lines and Bézier curves.
* Full visual customization of aforementioned elements, i.e. being able to change colour, line width, dash patterns etc.
