File ID with Magic Numbers
==========================
Pipeline data may be supplied in several different formats (bits in
memory). To handle these appropriately, the filetype needs to be
identified. The libmagic library provides a simple interface to get
descriptions and MIME types for supplied files, and this little project
experiments with its use.

Once a filetype (i.e. a format) has been determined, an appropriate
reader may be looked up and used to open the file. However, there are
several levels before and after the MIME type stage before data can
be used.

1. File access protocol - i.e. `file://`, `http://`, `ftp://` etc
    - libmagic can only handle local files, so cURL might need to be
      used to get MIME info for remote files (though this relies on
      the server being configured to report correct MIME type).
2. MIME type - handled, apart from the caveat above, by libmagic.
    - Protocol and type may interact, e.g. some readers might handle remote
      access directly, others may need the file to be downloaded first.
3. Data Schema - i.e. how the data is organised. **Distinct** from *format*,
for example we could support reading of XML files, but we could get an
  XML file whose schema is different (e.g. we want a top level `foo` tag,
  but the file contains a `bar` tag).


These considerations mean there are at least two stages to preparing data
for use:

1. Creation of a "reader" object for the data source (files in this case)
2. Validation of the data schema in the source (files again).


