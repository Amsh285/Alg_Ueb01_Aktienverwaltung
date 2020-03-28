#ifndef HASHTABLEDESERIALIZER_H
#define HASHTABLEDESERIALIZER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "Hashtable.h"
#include "HashTableDeserializerException.h"

#include "Json/JsonParser.h"
#include "Json/JsonNode.h"
#include "Json/JsonObject.h"
#include "Json/JsonValue.h"

class HashTableDeserializer
{
    public:
        HashTableDeserializer();
        virtual ~HashTableDeserializer();

        Hashtable* Deserialize(std::string path, int tableSize);
    protected:

    private:
        JsonNode* GetByName(std::string name, JsonObject* source);
        ShareContainer* BuildShareContainer(JsonObject* shareContainerObject);
        Share* BuildShare(JsonObject* shareObject);
        std::vector<ShareEntry*> BuildShareEntries(JsonObject* entryArrayObject);
};

#endif // HASHTABLEDESERIALIZER_H
