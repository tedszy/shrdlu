# shrdlu
Experiments in reading CSV documents.

Shrdlu breaks down the problem of parsing CSV data into three stages.

1. Writing Field_parser, which parses single fields of a CSV document.

2. Using Field_parser to make Record_parser, which parses one CSV record.

3. Using Record_parser to make Document_parser, which reads an
entire CSV document.

Shrdlu is easy to use. Just put an input stream into one of the parser
components, like so:

``` cpp

// Read one field.
Field_parser fp;
input_stream >> fp;
// now do something with fp or with fp.get_field().

// Read one record.
Record_parser rp;
input_sream >> rp;
// do something with rp or with rp.get_record();

// Read one document.
Document_parser dp;
input_stream >> dp;
// do something with dp or with dp.get_document();

```

To install shrdlu, clone the repo and run ```shell make ```. That will
build and run the tests. Look in ```shell test.cc ``` for examples.
