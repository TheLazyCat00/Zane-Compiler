// aliases.hpp - no PackageInfoMap needed
#pragma once

#include <llvm/IR/Module.h>
#include <map>
#include <string>
#include <filesystem>
#include <memory>

struct Package;

using Packages = std::map<std::string, std::unique_ptr<Package>>;
using Modules = std::map<std::string, std::unique_ptr<llvm::Module>>;

namespace fs = std::filesystem;
[[maybe_unused]] constexpr auto _clangd_fs_used = sizeof(fs::path);
