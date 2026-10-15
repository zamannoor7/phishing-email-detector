# Phishing Email Detector (C++)

I created a small C++ console program that checks an email for some common phishing warning signs. I'm still working on the code and improving my work, this is my first project and not a real email security product.

## Features
- Paste email text, ending with `END` on a separate line or load an email from a `.txt` file
- Look for urgent language, account verification requests, reward claims, and HTTP links
- Show matched warnings and a simple risk score

## How to Run
You need a C++ compiler.

```bash
g++ -std=c++11 main.cpp -o detector
./detector
```

On Windows, run `detector.exe` instead of `./detector`.

Choose `1` to paste text, or `2` to enter a file name such as `samples/suspicious.txt`.

## Concepts used
Functions, `if`/`else`, loops, strings, vectors, `find()`, and file input using `ifstream`.

## Limitations
This uses simple keyword matching so it can't verify sender identities, understand all URL formats, or confirm whether an email is malicious or not. Legitimate emails can receive high scores and phishing emails can receive low scores.

