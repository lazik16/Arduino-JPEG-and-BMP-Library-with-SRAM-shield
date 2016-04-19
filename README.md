# Arduino-JPEG-and-BMP-Library-with-SRAM-shield

Hello.

About 2 years I worked at the library Shield with support for compression and decompression of raster images (JPEG and BMP). It was a thesis.

I give here a source code and documentation of my work to use and further development.
The thesis is in Czech language codes but the comments are in English.
Also attach files for manufacturing Shield, which has not been verified. I worked on CTE LCD Shield. SRAM has been soldered in place EEPROM. The library is compatible with 8-bit and 32-bit platform with SS pin SRAM modification in the code.


Summary of the thesis:
The diploma thesis is focused on the compression and decompression of the image on the Arduino development platform. The work is divided into four parts. The first part is dedicated to the development platform Arduino. The introduction is a summary of the implementation of the Arduino platform as a tool for compression or decompression of raster image. Furthermore, there is disclosed a development environment and development boards, which were used for this work. The second part discusses the problem of image compression. There are described in detail raster format BMP and JPEG, including operations that take place during compression.

Another chapter deals with the design solution that allows realizing image compression and decompression on this platform. There is described a proposal expansion boards (Shield) containing additional SRAM memory that is compatible with 8 and 32-bit versions of Arduino. Also disclosed is a software solution that takes care of the operation of the Shield and realization of a raster image.

In conclusion, there are tests and experiments that were conducted as to verify the functionality and performance of the solution.

The aim of this work was to create a comprehensive solution for compression and decompression of raster image on the Arduino development platform. It supports BMP file format and basic sequential JPEG compression with color depth of 24 bits.
The entire hardware and software solutions have been tested at 8-bit and 32-bit version of the development platform Arduino.
From tests and experiments suggest that compression and decompression of raster image platform Arduino is realizable. Platform performance (especially 8-bit) is very low, therefore, time-consuming compression or decompression of the image is very high. The big problem is the lack of units working with a decimal point, causing a rapid rise time in the implementation of discrete cosine transform.
