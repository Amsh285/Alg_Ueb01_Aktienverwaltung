#ifndef HASHTABLESERIALIZER_H
#define HASHTABLESERIALIZER_H

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Hashtable.h"
#include "Share.h"
#include "ShareContainer.h"
#include "ShareEntry.h"

#include "Json/JsonNode.h"
#include "Json/JsonObject.h"
#include "Json/JsonUtilities.h"
#include "Json/JsonValue.h"

class HashTableSerializer
{
    public:
        HashTableSerializer();
        virtual ~HashTableSerializer();

        void SerializeHashTable(Hashtable* table, std::string path);
    protected:

    private:
        void BuildShareContainer(ShareContainer* container, JsonObject* rootElement, int hashTableIndex);
        void BuildShare(Share* value, JsonObject* rootElement);
        void BuildShareEntry(ShareEntry* value, JsonObject* shareNode);
};

#endif // HASHTABLESERIALIZER_H
