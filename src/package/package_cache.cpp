#include "package/package.hpp"

#include "globals/constants.hpp"
#include "ir/nodes.hpp"

#include <cereal/archives/binary.hpp>
#include <fstream>

void Package::writeSymbolsCache(
		std::shared_ptr<ir::PackageInfo> packageInfo,
		const std::string& packageDir) {
	fs::path symbolsPath = constants::getSymbolsPath(packageDir);
	fs::create_directories(symbolsPath.parent_path());

	std::ofstream os(symbolsPath, std::ios::binary);
	cereal::BinaryOutputArchive archive(os);

	archive(
		packageInfo->packageName,
		packageInfo->importedPackages
	);
}
