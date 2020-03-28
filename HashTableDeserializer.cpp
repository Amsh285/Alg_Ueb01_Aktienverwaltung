#include "HashTableDeserializer.h"

HashTableDeserializer::HashTableDeserializer()
{
    //ctor
}

HashTableDeserializer::~HashTableDeserializer()
{
    //dtor
}

Hashtable* HashTableDeserializer::Deserialize(std::string path, int tableSize)
{
    std::ifstream inputStream(path);

    if (!inputStream)
        throw HashTableDeserializerException("Could not read File: " + path + ".");

    inputStream.seekg(0, std::ios::end);
    size_t len = inputStream.tellg();
    inputStream.seekg(0);

    std::string contents(len + 1, '\0');
    inputStream.read(&contents[0], len);
    inputStream.close();

    JsonParser parser;

    Hashtable* result = new Hashtable(tableSize);

    //std::cout << std::endl << "fileString:" << contents << std::endl << std::endl;

    JsonObject* root = (JsonObject*)parser.ParseJsonString(contents);

    std::vector<JsonNode*> shareContainerObjects = root->GetChildren();
    ShareContainer** hashTableItemContainer = result->GetItems();

    for(unsigned int i = 0;i < shareContainerObjects.size();++i)
    {
        JsonObject* shareContainerObject = (JsonObject*)shareContainerObjects[i];
        ShareContainer* container = BuildShareContainer(shareContainerObject);

        JsonValue* indexValue = (JsonValue*)GetByName("hashTableIndex", shareContainerObject);
        int index = std::stoi(indexValue->GetValue());

        hashTableItemContainer[index] = container;
    }

    delete root;
    return result;
}

JsonNode* HashTableDeserializer::GetByName(std::string name, JsonObject* source)
{
    if(source == nullptr)
        throw std::invalid_argument("source cannot be null.");

    std::vector<JsonNode*> children = source->GetChildren();

    for(unsigned int i = 0;i < children.size();++i)
    {
        JsonNode* current = children[i];

        if(current->GetName() == name)
            return current;
    }

    return nullptr;
}

ShareContainer* HashTableDeserializer::BuildShareContainer(JsonObject* shareContainerObject)
{
    if(shareContainerObject == nullptr)
        throw std::invalid_argument("shareContainerObject cannot be null.");

    JsonValue* valueObject = (JsonValue*)GetByName("hasValue", shareContainerObject);
    int hasValue = std::stoi(valueObject->GetValue());

    if(hasValue)
    {
        JsonObject* shareObject = (JsonObject*)GetByName("value", shareContainerObject);
        Share* value = BuildShare(shareObject);

        return new ShareContainer(value);
    }

    return new ShareContainer();
}

Share* HashTableDeserializer::BuildShare(JsonObject* shareObject)
{
    if(shareObject == nullptr)
        throw std::invalid_argument("shareObject cannot be null.");

    JsonValue* nameValue = (JsonValue*)GetByName("name", shareObject);
    JsonValue* tokenValue = (JsonValue*)GetByName("token", shareObject);
    JsonValue* isinValue = (JsonValue*)GetByName("isin", shareObject);

    Share* result = new Share(nameValue->GetValue(), tokenValue->GetValue(), isinValue->GetValue());

    JsonObject* entryArrayObject = (JsonObject*)GetByName("shareEntries", shareObject);
    std::vector<ShareEntry*> entries = BuildShareEntries(entryArrayObject);
    result->setEntries(entries);

    return result;
}

std::vector<ShareEntry*> HashTableDeserializer::BuildShareEntries(JsonObject* entryArrayObject)
{
    if(entryArrayObject == nullptr)
        throw std::invalid_argument("entryArrayObject cannot be null.");

    std::vector<ShareEntry*> result;

    std::vector<JsonNode*> shareEntryObjects = entryArrayObject->GetChildren();

    for(unsigned int i = 0;i < shareEntryObjects.size();++i)
    {
        JsonObject* shareEntryObject = (JsonObject*)shareEntryObjects[i];

        JsonValue* dateValue = (JsonValue*)GetByName("date", shareEntryObject);

        JsonValue* openValue = (JsonValue*)GetByName("open", shareEntryObject);
        JsonValue* highValue = (JsonValue*)GetByName("high", shareEntryObject);
        JsonValue* lowValue = (JsonValue*)GetByName("low", shareEntryObject);
        JsonValue* closeValue = (JsonValue*)GetByName("close", shareEntryObject);
        JsonValue* volumeValue = (JsonValue*)GetByName("volume", shareEntryObject);
        JsonValue* adjustedCloseValue = (JsonValue*)GetByName("adjustedClose", shareEntryObject);

        double open = std::stod(openValue->GetValue());
        double high = std::stod(highValue->GetValue());
        double low = std::stod(lowValue->GetValue());
        double close = std::stod(closeValue->GetValue());
        double volume = std::stod(volumeValue->GetValue());
        double adjustedClose = std::stod(adjustedCloseValue->GetValue());

        ShareEntry* value = new ShareEntry(dateValue->GetValue(), open, high, low, close, volume, adjustedClose);
        result.push_back(value);
    }

    return result;
}

