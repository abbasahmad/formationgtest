rm -rf allure-results/*
cp --parents bazel-testlogs/*/*/test.xml allure-results/
allure generate allure-results/*/*/* --clean -o allure-report --single-file