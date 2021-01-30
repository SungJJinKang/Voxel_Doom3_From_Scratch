#include "AssetImporterWorker_Texture.h"

namespace doom
{
	namespace assetimporter
	{
		extern template class AssetApiImporter<Asset::eAssetType::TEXTURE>;

		template std::optional <Asset::asset_type_t<Asset::eAssetType::TEXTURE>> ReadAssetFile<Asset::eAssetType::TEXTURE>(std::filesystem::path path);

		template <>
		std::optional <Asset::asset_type_t<Asset::eAssetType::TEXTURE>> ReadAssetFile<Asset::eAssetType::TEXTURE>(std::filesystem::path path)
		{
			return {};
		}
	}
}