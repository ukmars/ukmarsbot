#
# Example python script to generate a BOM from a KiCad generic netlist
#
# Example: Sorted and Grouped CSV BOM
#
# Mofified Sep 2022, Peter Harrison, UKMARS
#

"""
    @package
    Output: CSV (comma-separated)
    Grouped By: Value, Footprint
    Sorted By: Ref
    Fields: Ref, Value, Qnty, Note, Package, Vendor, Datasheet

    Command line:
    python "pathToFile/bom_csv_grouped_by_value_no_fp.py" "%I" "%O.csv"
"""

# Import the KiCad python helper module and the csv formatter
import kicad_netlist_reader
import kicad_utils
import csv
import sys

# A helper function to convert a UTF8/Unicode/locale string read in netlist
# for python2 or python3
def fromNetlistText( aText ):
    if sys.platform.startswith('win32'):
        try:
            return aText.encode('utf-8').decode('cp1252')
        except UnicodeDecodeError:
            return aText
    else:
        return aText

# Generate an instance of a generic netlist, and load the netlist tree from
# the command line option. If the file doesn't exist, execution will stop
net = kicad_netlist_reader.netlist(sys.argv[1])

# Open a file to write to, if the file cannot be opened output to stdout instead
try:
    f = kicad_utils.open_file_write(sys.argv[2], 'w')
except IOError:
    e = "Can't open output file for writing: " + sys.argv[2]
    print(__file__, ":", e, sys.stderr)
    f = sys.stdout

# Create a new csv writer object to use as the output formatter
out = csv.writer(f, delimiter=',', quotechar='"', escapechar='',quoting=csv.QUOTE_NONNUMERIC)

# Output The header
out.writerow(['Ref', 'Value', 'Qty', 'Note', 'Package','Vendor','Datasheet'])


# Get all of the components in groups of matching parts + values
# (see ky_generic_netlist_reader.py)
grouped = net.groupComponents()

# Output all of the component information
for group in grouped:
    refs = ""

    # Add the reference of every component in the group and keep a reference
    # to the component so that the other data can be filled in once per group
    for component in group:
        refs += fromNetlistText( component.getRef() ) + ", "
        c = component
    refs = refs[:-2] ## drop the trailing comma
    
    # Fill in the component groups common data
    note = fromNetlistText(c.getField("Note"))

    out.writerow([
        refs,
        fromNetlistText( c.getValue() ),
        len(group),
        note,
        fromNetlistText( c.getField("Package") ),
        fromNetlistText( c.getField("Vendor") ),
        fromNetlistText( c.getDatasheet() ),
        ])

