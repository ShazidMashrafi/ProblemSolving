    int num = 42; // Example number (00101010 in binary)
    cout << "Number: " << num << " (Binary: " << bitset<8>(num) << ")\n";
    int pos = 3; // Bit position (0-based index)
    cout << "Set bit at " << pos << ": " << bitset<8>(num | (1 << pos)) << endl;
    cout << "Clear bit at " << pos << ": " << bitset<8>(num & ~(1 << pos)) << endl;
    cout << "Toggle bit at " << pos << ": " << bitset<8>(num ^ (1 << pos)) << endl;
    cout << "Is bit " << pos << " set? " << ((num & (1 << pos)) ? "Yes" : "No") << endl;
    cout << "Set bits: " << __builtin_popcount(num) << endl;
    cout << "First set bit pos (1-based): " << __builtin_ffs(num) << endl;
    cout << "Highest set bit pos (0-based): " << (31 - __builtin_clz(num)) << endl;
    cout << "Is power of two? " << ((num && !(num & (num - 1))) ? "Yes" : "No") << endl;
    cout << num << " is " << (num & 1 ? "Odd" : "Even") << endl;
    cout << num << " * 2 = " << (num << 1) << ", " << num << " / 2 = " << (num >> 1) << endl;
    int a = 5, b = 9;
    cout << "Swap: a = " << a << ", b = " << b;
    a ^= b; b ^= a; a ^= b;
    cout << " -> a = " << a << ", b = " b << endl;
    // Number System Conversions
    cout << "Binary: " << bitset<8>(num) << ", Octal: " << oct << num
         << ", Hex: " << hex << uppercase << num << endl;
    // Convert Binary, Octal, Hexadecimal to Decimal
    cout << "Binary to Decimal: " << stoi("101010", 0, 2) << ", "
         << "Octal to Decimal: " << stoi("52", 0, 8) << ", "
         << "Hex to Decimal: " << stoi("2A", 0, 16) << endl;
