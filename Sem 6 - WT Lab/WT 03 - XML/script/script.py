import os
from lxml import etree

def transform_xml_to_html(xml_file, xsl_file, output_file):
    # Load XML and XSL files
    xml_doc = etree.parse(xml_file)
    xsl_doc = etree.parse(xsl_file)

    # Create XSLT transformer
    transform = etree.XSLT(xsl_doc)

    # Appply transformation
    result_tree = transform(xml_doc)

    # Save the result to HTML file
    result_tree.write(output_file, pretty_print=True)


if __name__ == "__main__":
    xml_file = os.path.abspath("D:\\Academic-Assignments\\Sem 6 - WT Lab\\WT 03 - XML\\xml\\employees.xml")
    xsl_file = os.path.abspath("D:\\Academic-Assignments\\Sem 6 - WT Lab\\WT 03 - XML\\xsl\\employees.xsl")
    output_file = os.path.abspath("D:\\Academic-Assignments\\Sem 6 - WT Lab\\WT 03 - XML\\output\\index.html")

    transform_xml_to_html(xml_file, xsl_file, output_file)