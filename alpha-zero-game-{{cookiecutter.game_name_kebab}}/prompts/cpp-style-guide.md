# C++ Style Guide

Strictly follow Google's C++ style guide. It's okay to use the one you know
during training time, no need to look it up on the internet unless you don't
remember certain details.

## Key things to remember

- Headers are `.h`, implementations are `.cc`.
- Use CamelCase for function and method names.
- We're using C++23, although the style guide does not recommend C++23 yet.
- Do not use `auto` type. Use `using ...` in an anonymous namespace (`.cc` files
  only), add aliases for commonly used custom types if the type is too long.
