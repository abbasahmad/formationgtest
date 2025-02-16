#!/bin/bash

# Ensure allure-results directory exists
mkdir -p allure-results

# Remove any existing Allure result files
rm -rf allure-results/*

# Copy Bazel test results to allure-results
cp --parents bazel-testlogs/*/*/test.xml allure-results/

# Generate Allure report as a single file
allure generate allure-results/*/*/* --clean -o allure-report --single-file
