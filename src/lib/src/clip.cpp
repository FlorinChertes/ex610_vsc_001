#include <clip.h>

#include <read_from_disk.h>
#include <write_to_disk.h>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename T>
const char * file_extension()
{
    throw std::runtime_error(std::string("No file extension set for ") + typeid(T).name());
}

template<> 
const char * file_extension<int>() { return ".int"; }

template<> 
const char * file_extension<float>() { return ".float"; }

template<> 
const char * file_extension<bool>() { return ".bool"; }

template<> 
const char * file_extension<std::string>() { return ".string"; }


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename T>
void registerContributionFileType(Contribution_basis::FactoryType * factory)
{
    std::string extension = file_extension<T>();

    try {
        factory->add<Contribution_typed<T> >(extension);
    } catch(const std::logic_error &) {
        std::runtime_error("File extension " + extension + " cannot be used twice for contributions");
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<>
void Contribution_basis::FactoryType::init()
{
    registerContributionFileType<int>(this);
    registerContributionFileType<float>(this);
    registerContributionFileType<bool>(this);
    registerContributionFileType<std::string>(this);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Contribution_basis::Ptr Contribution_basis::readFrom(const boost::filesystem::path & path)
{
    namespace fs = boost::filesystem;

    Contribution_basis::Ptr instance = nullptr;

    const auto file_name = path.filename().string();

    const auto extensionStart = file_name.find('.');
    if(extensionStart == std::string::npos) {
        std::cout << "File " << path.string() << " has no extension.\n";
        return nullptr;
    }

    const std::string ext = file_name.substr(extensionStart);

    try {
        static FactoryType factory;
        instance = factory.create(ext);
        instance->_readFrom(path);
    } catch(const std::out_of_range & e) {
        std::cout << "While reading from " << path << ": " <<  e.what() << std::endl;
    }

    return instance;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename T>
void Contribution_typed<T>::_readFrom(const boost::filesystem::path &path)
{
    _content = readFromDisk<T>(path);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using WriteLock = std::lock_guard<std::mutex>;
using ReadLock = WriteLock; // Replace by shared_lock in c++17

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::string Contribution_basis::to_string() const
{
	const std::string s("Contribution::to_string");
	return s;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::string Contribution_derived::name() const
{ 
	return "name: Contribution_derived"; 
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Contribution_derived::writeTo(const boost::filesystem::path & path)
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename T>
void Contribution_typed<T>::writeTo(const boost::filesystem::path & path)
{
    std::cout << "Write to disk using path: " << path << "\n";
    try {
		boost::filesystem::path file_name_ext = path.string() + file_extension<T>();
    	std::cout << "Write to disk using path: " << file_name_ext << "\n";		
        writeToDisk(_content, file_name_ext);
    } catch(const std::logic_error & e) {
        std::cout << "Failed to write " << path << ": " << e.what();
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Contribution_map::setContributionPtr(const std::string &key, 
										  const Contribution_basis::Ptr value, 
										  const std::string &storageName)
{
    WriteLock lock(_mutex);
    std::cout << "set storage: " << storageName << " key: " << key << "\n";
    _contributions[storageName][key] = value;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Contribution_basis::Ptr Contribution_map::getContributionPtr(const std::string &storageName, 
														   const std::string &key) const
{
    try {
        ReadLock lock(_mutex);
    	std::cout << "get storage: " << storageName << " key: " << key << "\n";		
        return  _contributions.at(storageName).at(key);
    } catch(const std::out_of_range &) {
        throw std::range_error("Missing contribution: " + key + " in storage: " + storageName);
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
const Contribution_map::Storage & Contribution_map::getContributions(const std::string & storageName) const
{
    try {
        // TODO: once the storage reference is "out there", no thread safety can be guaranteed
        ReadLock lock(_mutex);
        return _contributions.at(storageName);
    } catch(const std::out_of_range &) {
        throw std::range_error("No such storage: " + storageName);
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Contribution_typed<int> temp_int(42);
Contribution_typed<std::string> temp_string("Eva");

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void writeContributions(const Contribution_map & contributable,
							  const std::string & storage_name,
							  const boost::filesystem::path & storage_path)
{
    namespace fs = boost::filesystem;

    if( fs::is_directory(storage_path) ) {
        for(const auto & pair : contributable.getContributions(storage_name)) {

            const auto & key = pair.first;
            pair.second->writeTo(storage_path / key);
        }
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void readContributions(Contribution_map & contributable,
					   const std::string & storage_name,
					   const boost::filesystem::path & storage_path)
{
    namespace fs = boost::filesystem;

    if( fs::is_directory(storage_path) ) {
        for(fs::directory_iterator it(storage_path); it != fs::directory_iterator(); ++it) {

            const auto & path_name = it->path();

            auto contribution_name = path_name.filename().string();
            contribution_name = contribution_name.substr(0, contribution_name.find('.'));
            auto contribution = Contribution_basis::readFrom(path_name);
            if(contribution != nullptr) {
                std::cout << "contribution exists: " << contribution_name << "\n";
                contributable.setContributionPtr(contribution_name, contribution, storage_name);
            }
        }
    }
}
