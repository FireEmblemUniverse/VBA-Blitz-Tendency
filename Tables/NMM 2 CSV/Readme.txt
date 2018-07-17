Nightmare Module to CSV to EA converter v1.0
by Circleseverywhere

This tool rips data tables from a rom to CSV format
using a nightmare module as a template.

Note that you can use EA definitions instead of numbers
in your cells. NMM2CSV comes with a basic definitions file called
"Table Definitions.txt". You can add your own definitions
to this document, replace and/or include your own.

N2C.exe instructions:

EITHER

Place your .nmm files in the same parent directory as
N2C.exe and run N2C.exe. In the File Select dialog,
select the rom you wish to rip from and click OK.

OR

Place your .nmm files in the same parent directory as
the rom you wish to rip from (subdirectories included)
and simply drag and drop the rom onto n2c.exe.

This will generate a CSV file for each nmm in the folder,
which you can edit with any spreadsheet software e.g.
Excel or Google Docs.

C2EA.exe instructions:

Place C2EA.exe in the same parent directory as your NMM
and CSV files, and run it. It will create .event files
for each table, and an EA installer file called
"Table Installer.txt" which can install the tables
or be #included in a project buildfile.

If you have repointed any tables by writing INLINE LabelName
in the first cell, you can either drag a rom onto C2EA.exe
or choose it from the file selection dialog.

Notes on the CSV Format:
The first cell of the CSV table contains the offset of the
table in the ROM. By default this is the same as in the
NMM, but you can change this if you have repointed your
table. You can also input a #defined value, e.g. ItemTable
where you have "#define ItemTable <offset of the new item table>"
in your definitions file.

You can expand and repoint a table by replacing the first cell with
INLINE LabelName
which will place the table in free space and defines the offset of
the table as LabelName. C2EA will use the PFinder tool included with
Event Assembler to automatically find and update pointers to the table.

Special thanks to Zahlman for making the code less bad.
