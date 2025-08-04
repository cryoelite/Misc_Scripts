"use strict";

const fs = require("node:fs");
const path = require("node:path");
const cheerio = require("cheerio");

function main() {
  const args = process.argv.slice(2);
  if (args.length !== 3) {
    console.log(
      "Usage: node parse_gdoc_with_links_html_file.js <html_file> <template_file> <output_dir>"
    );
    return;
  }

  const [htmlFile, templateFile, outputDir] = args;

  fs.readFile(htmlFile, "utf-8", (err, data) => {
    if (err) {
      console.log(`Error: ${err}`);
      return;
    }
    const $ = cheerio.load(data);
    const links = $("a");

    const hackerrankLinks = links
      .map((i, el) => $(el).attr("href"))
      .get()
      .filter((href) => href.includes("hackerrank"));

    hackerrankLinks.forEach((url, i) => {
      const urlParts = url.split("/");
      const name = urlParts[urlParts.length - 1].split("?")[0];
      setupFolder(url, name, i + 1, templateFile, outputDir);
    });
  });
}

function setupFolder(url, name, index, templateFile, outputDir) {
  const problemDir = path.join(outputDir, `${index}_HR_${name}`);
  const problemFile = path.join(problemDir, "problem.cpp");
  const inputFile = path.join(problemDir, "input.txt");
  const outputFile = path.join(problemDir, "output.txt");
  const carShFile = path.join(problemDir, "car.sh");
  const solutionDocFile = path.join(problemDir, "solution.md");

  const commentedURL = `// ${url} \n`;
  const carShContent = `#!/bin/bash
  echo "Getting env variable"
  env_var=$(<../../.env)
  export "\${env_var?}"=true
  clang++ problem.cpp -o problem -std=c++20 && ./problem
  `;

  try {
    fs.mkdirSync(problemDir, { recursive: true });
    const templateData = fs.readFileSync(templateFile);
    const fd = fs.openSync(problemFile, "w+");
    const buffer = Buffer.from(commentedURL);

    fs.writeSync(fd, buffer, 0, buffer.length, 0);
    fs.writeSync(fd, templateData, 0, templateData.length, buffer.length);
    fs.closeSync(fd);

    fs.writeFileSync(inputFile, "");
    fs.writeFileSync(outputFile, "");
    fs.writeFileSync(solutionDocFile, "");
    fs.writeFileSync(carShFile, carShContent, { mode: 0o755 });

    console.log(`${problemFile} written successfully`);
  } catch (err) {
    console.log(`Failed to set up problem ${index} with name ${name}: ${err}`);
  }
}

main();
