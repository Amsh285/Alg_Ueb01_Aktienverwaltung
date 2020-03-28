#include "HashTableSerializer.h"

HashTableSerializer::HashTableSerializer()
{
    //ctor
}

HashTableSerializer::~HashTableSerializer()
{
    //dtor
}

void HashTableSerializer::SerializeHashTable(Hashtable* table,  std::string path)
{
    if(table == nullptr)
        throw std::invalid_argument("table cannot be null.");

    ShareContainer** containerTable = table->GetItems();
    int containerTableSize = table->GetTableSize();

    JsonObject* root = Create::A.JsonObject()
        .WithJsonObjectType(JsonObjectType_Array)
        .Build();

    for(int i = 0;i < containerTableSize;++i)
    {
        if(containerTable[i] != nullptr)
            BuildShareContainer(containerTable[i], root, i);
    }

    std::ofstream outStream (path, std::ofstream::out);
    outStream << root->ToJsonString();
    outStream.close();

    delete root;
}

void HashTableSerializer::BuildShareContainer(ShareContainer* container, JsonObject* rootElement, int hashTableIndex)
{
    if(container == nullptr || rootElement == nullptr)
        throw std::invalid_argument("container and rootElement cannot be null.");

    JsonObject* shareContainerNode = Create::A.JsonObject()
        .WithJsonObjectType(JsonObjectType_Object)
        .WithParent(rootElement)
        .Build();

    // Der Wert gehört eigentlich nicht zu Datenstruktur, wird dazugehackt um den index in der hashtable zu speichern.
    Create::A.JsonValue()
        .WithParent(shareContainerNode)
        .WithName("hashTableIndex")
        .WithValue(hashTableIndex)
        .Build();

    Create::A.JsonValue()
        .WithParent(shareContainerNode)
        .WithName("hasValue")
        .WithRawValue(std::to_string(container->HasValue()))
        .Build();

    if(container->HasValue())
        BuildShare(container->GetValue(), shareContainerNode);
}

void HashTableSerializer::BuildShare(Share* value, JsonObject* shareContainerNode)
{
    if(value == nullptr || shareContainerNode == nullptr)
        throw std::invalid_argument("value and shareContainerNode cannot be null.");

    JsonObject* shareObject = Create::A.JsonObject()
        .WithParent(shareContainerNode)
        .WithJsonObjectType(JsonObjectType_Object)
        .WithName("value")
        .Build();

    Create::A.JsonValue()
        .WithParent(shareObject)
        .WithName("name")
        .WithValue(value->GetName())
        .Build();

    Create::A.JsonValue()
        .WithParent(shareObject)
        .WithName("token")
        .WithValue(value->GetToken())
        .Build();

    Create::A.JsonValue()
        .WithParent(shareObject)
        .WithName("isin")
        .WithValue(value->GetIsin())
        .Build();

    JsonObject* shareEntryVectorObject = Create::A.JsonObject()
        .WithParent(shareObject)
        .WithJsonObjectType(JsonObjectType_Array)
        .WithName("shareEntries")
        .Build();

    std::vector<ShareEntry*> shareEntries = value->GetShareEntries();

    for(int i = 0;i < shareEntries.size();++i)
        BuildShareEntry(shareEntries[i], shareEntryVectorObject);
}

void HashTableSerializer::BuildShareEntry(ShareEntry* value, JsonObject* shareEntryVectorObject)
{
    if(value == nullptr || shareEntryVectorObject == nullptr)
        throw std::invalid_argument("value and shareEntryVectorObject cannot be null.");

    JsonObject* shareEntryObject = Create::A.JsonObject()
        .WithParent(shareEntryVectorObject)
        .WithJsonObjectType(JsonObjectType_Object)
        .Build();

    Create::A.JsonValue()
        .WithParent(shareEntryObject)
        .WithName("date")
        .WithValue(value->GetDate())
        .Build();

    Create::A.JsonValue()
        .WithParent(shareEntryObject)
        .WithName("open")
        .WithValue(value->GetOpen())
        .Build();

    Create::A.JsonValue()
        .WithParent(shareEntryObject)
        .WithName("high")
        .WithValue(value->GetHigh())
        .Build();

    Create::A.JsonValue()
        .WithParent(shareEntryObject)
        .WithName("low")
        .WithValue(value->GetLow())
        .Build();

    Create::A.JsonValue()
        .WithParent(shareEntryObject)
        .WithName("close")
        .WithValue(value->GetClose())
        .Build();

    Create::A.JsonValue()
        .WithParent(shareEntryObject)
        .WithName("volume")
        .WithValue(value->GetVolume())
        .Build();

    Create::A.JsonValue()
        .WithParent(shareEntryObject)
        .WithName("adjustedClose")
        .WithValue(value->GetAdjustedClose())
        .Build();
}
