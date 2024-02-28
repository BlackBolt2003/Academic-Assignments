# XML Processing Project

This project is designed to process employee information using XML, DTD, XML Schema, XSLT, and CSS. The project structure is organized as follows:

## Directories and Files

### xml/

Contains all XML-related files.

- **employees.xml:** The main XML file that stores employee information.
- **employees.dtd:** The DTD file defining the structure of the XML document.
- **employees.xsd:** The XML Schema file for validation.

### xsl/

Contains XSL and CSS files.

- **employees.xsl:** The XSLT file for transforming XML to HTML.
- **style.css:** The CSS file for styling the HTML output.

### output/

This directory is where the processed files will be saved.

- **index.html:** The final HTML output after applying XSLT transformation.

### script/

Contains a script or program to automate the processing of XML and XSL files.

- **script.py:** Python script that applies XSLT transformation to generate HTML.

## Usage

To process the XML and XSL files and generate HTML output, follow these steps:

1. Ensure that the necessary libraries (e.g., lxml) are installed (if using Python). `pip install lxml`.
2. Execute the script `script.py` in the `script/` directory.