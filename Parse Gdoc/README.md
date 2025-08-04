# Parse Gdoc

This directory contains a Node.js script to parse a Google Doc HTML file, extract HackerRank links, and set up a directory structure for solving the problems in C++.

## How to use

### Prerequisites
- Node.js installed.
- A C++ template file.

### Installation
1.  Navigate to the `Parse Gdoc` directory.
2.  Install the dependencies:
    ```bash
    npm install
    ```

### Usage
1.  Export your Google Doc with the HackerRank links as an HTML file and save it in this directory.
2.  Update the `filePath` variable in `parse_gdoc_with_links_html_file.js` to point to your HTML file.
3.  Update the `templateFile` and `problemDir` variables to match your desired C++ template and output directory.
4.  Run the script:
    ```bash
    node parse_gdoc_with_links_html_file.js
    ```

The script will create a directory for each HackerRank link found in the HTML file, and each directory will contain a C++ file based on your template, along with `input.txt`, `output.txt`, `solution.md` and `car.sh` files.
