# About:
Its a small binary file parser ( no streaming for now ). Parser doesnt interpret raw bytes as an onject. it checks bounds & for guarantees error string for invalid inputs

# Scalability / Issues
1. Huge files > memory will need streaming
2. No unicode byte validation here
3. Fixed format used here

# build
build :
cmake --build . --config Debug --verbose

test :
ctest -C Debug
