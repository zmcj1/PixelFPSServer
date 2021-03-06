#pragma once

#include <vector>
#include <cstdint>
#include <cstring>

using namespace std;

enum class NetworkMessage : uint32_t
{
    //unuse start
    Unknown = 0,
    Server_GetStatus,
    Server_GetPing,
    //unuse end

    Client_Accepted,
    Client_AssignID,
    Client_RegisterWithServer,
    Client_UnregisterWithServer,

    Game_AddPlayer,
    Game_RemovePlayer,
    Game_UpdatePlayer,
    Game_BulletHitOther,
    Game_ImDead,
    Game_IRespawn,
    Game_HostChooseMode, //this value should be sent by Host.
    Game_ZombieModeStart,
};

enum class NetworkType
{
    None = 0,
    Host = 1,   //server + client
    Client = 2, //client
};

struct NetBullet
{
public:
    uint32_t id;
    float x;
    float y;

    NetBullet()
    {
    }

    NetBullet(int id, float x, float y)
    {
        this->id = id;
        this->x = x;
        this->y = y;
    }
};

struct PlayerNetData
{
public:
    uint32_t uniqueID = 0;
    float posX;
    float posY;
    int health;
    vector<NetBullet> bullets;

    std::vector<uint8_t> Serialize() const
    {
        std::vector<uint8_t> buffer;

        size_t pointer = 0;

        buffer.resize(buffer.size() + sizeof(uint32_t));
        std::memcpy(buffer.data() + pointer, &uniqueID, sizeof(uint32_t));
        pointer += sizeof(uint32_t);

        buffer.resize(buffer.size() + sizeof(float));
        std::memcpy(buffer.data() + pointer, &posX, sizeof(float));
        pointer += sizeof(float);

        buffer.resize(buffer.size() + sizeof(float));
        std::memcpy(buffer.data() + pointer, &posY, sizeof(float));
        pointer += sizeof(float);

        buffer.resize(buffer.size() + sizeof(int));
        std::memcpy(buffer.data() + pointer, &health, sizeof(int));
        pointer += sizeof(int);

        //bullets:
        for (const NetBullet bullet : bullets)
        {
            //id:
            buffer.resize(buffer.size() + sizeof(uint32_t));
            std::memcpy(buffer.data() + pointer, &bullet.id, sizeof(uint32_t));
            pointer += sizeof(uint32_t);

            //x:
            buffer.resize(buffer.size() + sizeof(float));
            std::memcpy(buffer.data() + pointer, &bullet.x, sizeof(float));
            pointer += sizeof(float);

            //y:
            buffer.resize(buffer.size() + sizeof(float));
            std::memcpy(buffer.data() + pointer, &bullet.y, sizeof(float));
            pointer += sizeof(float);
        }

        return buffer;
    }

    void Deserialize(const std::vector<uint8_t>& buffer)
    {
        size_t pointer = 0;

        std::memcpy(&uniqueID, buffer.data() + pointer, sizeof(uint32_t));
        pointer += sizeof(uint32_t);

        std::memcpy(&posX, buffer.data() + pointer, sizeof(float));
        pointer += sizeof(float);

        std::memcpy(&posY, buffer.data() + pointer, sizeof(float));
        pointer += sizeof(float);

        std::memcpy(&health, buffer.data() + pointer, sizeof(int));
        pointer += sizeof(int);

        //bullets:
        int diff = buffer.size() - pointer;
        bullets.clear();
        for (int i = 0; i < (diff / sizeof(NetBullet)); i++)
        {
            NetBullet bullet;

            std::memcpy(&bullet.id, buffer.data() + pointer, sizeof(uint32_t));
            pointer += sizeof(uint32_t);

            std::memcpy(&bullet.x, buffer.data() + pointer, sizeof(float));
            pointer += sizeof(float);

            std::memcpy(&bullet.y, buffer.data() + pointer, sizeof(float));
            pointer += sizeof(float);

            bullets.push_back(bullet);
        }
    }
};

struct BulletHitInfo
{
public:
    uint32_t myID;
    uint32_t otherPlayerID;
    float damage;

    std::vector<uint8_t> Serialize() const
    {
        std::vector<uint8_t> buffer;

        size_t pointer = 0;

        buffer.resize(buffer.size() + sizeof(uint32_t));
        std::memcpy(buffer.data() + pointer, &myID, sizeof(uint32_t));
        pointer += sizeof(uint32_t);

        buffer.resize(buffer.size() + sizeof(uint32_t));
        std::memcpy(buffer.data() + pointer, &otherPlayerID, sizeof(uint32_t));
        pointer += sizeof(uint32_t);

        buffer.resize(buffer.size() + sizeof(float));
        std::memcpy(buffer.data() + pointer, &damage, sizeof(float));
        pointer += sizeof(float);

        return buffer;
    }

    void Deserialize(const std::vector<uint8_t>& buffer)
    {
        size_t pointer = 0;

        std::memcpy(&myID, buffer.data() + pointer, sizeof(uint32_t));
        pointer += sizeof(uint32_t);

        std::memcpy(&otherPlayerID, buffer.data() + pointer, sizeof(uint32_t));
        pointer += sizeof(uint32_t);

        std::memcpy(&damage, buffer.data() + pointer, sizeof(float));
        pointer += sizeof(float);
    }
};

struct ImDead
{
public:
    uint32_t ID;
    uint32_t killerID;

    std::vector<uint8_t> Serialize() const
    {
        std::vector<uint8_t> buffer;

        size_t pointer = 0;

        buffer.resize(buffer.size() + sizeof(uint32_t));
        std::memcpy(buffer.data() + pointer, &ID, sizeof(uint32_t));
        pointer += sizeof(uint32_t);

        buffer.resize(buffer.size() + sizeof(uint32_t));
        std::memcpy(buffer.data() + pointer, &killerID, sizeof(uint32_t));
        pointer += sizeof(uint32_t);

        return buffer;
    }

    void Deserialize(const std::vector<uint8_t>& buffer)
    {
        size_t pointer = 0;

        std::memcpy(&ID, buffer.data() + pointer, sizeof(uint32_t));
        pointer += sizeof(uint32_t);

        std::memcpy(&killerID, buffer.data() + pointer, sizeof(uint32_t));
        pointer += sizeof(uint32_t);
    }
};

struct IRespawn
{
public:
    uint32_t uniqueID = 0;
    float posX;
    float posY;
    int health;

    std::vector<uint8_t> Serialize() const
    {
        std::vector<uint8_t> buffer;

        size_t pointer = 0;

        buffer.resize(buffer.size() + sizeof(uint32_t));
        std::memcpy(buffer.data() + pointer, &uniqueID, sizeof(uint32_t));
        pointer += sizeof(uint32_t);

        buffer.resize(buffer.size() + sizeof(float));
        std::memcpy(buffer.data() + pointer, &posX, sizeof(float));
        pointer += sizeof(float);

        buffer.resize(buffer.size() + sizeof(float));
        std::memcpy(buffer.data() + pointer, &posY, sizeof(float));
        pointer += sizeof(float);

        buffer.resize(buffer.size() + sizeof(int));
        std::memcpy(buffer.data() + pointer, &health, sizeof(int));
        pointer += sizeof(int);

        return buffer;
    }

    void Deserialize(const std::vector<uint8_t>& buffer)
    {
        size_t pointer = 0;

        std::memcpy(&uniqueID, buffer.data() + pointer, sizeof(uint32_t));
        pointer += sizeof(uint32_t);

        std::memcpy(&posX, buffer.data() + pointer, sizeof(float));
        pointer += sizeof(float);

        std::memcpy(&posY, buffer.data() + pointer, sizeof(float));
        pointer += sizeof(float);

        std::memcpy(&health, buffer.data() + pointer, sizeof(int));
        pointer += sizeof(int);
    }
};

struct HostChoose
{
public:
    uint32_t uniqueID = 0;
    int gameMode = 0;
    int soloWeapon = 0;

    std::vector<uint8_t> Serialize() const
    {
        std::vector<uint8_t> buffer;

        size_t pointer = 0;

        buffer.resize(buffer.size() + sizeof(uint32_t));
        std::memcpy(buffer.data() + pointer, &uniqueID, sizeof(uint32_t));
        pointer += sizeof(uint32_t);

        buffer.resize(buffer.size() + sizeof(int));
        std::memcpy(buffer.data() + pointer, &gameMode, sizeof(int));
        pointer += sizeof(int);

        buffer.resize(buffer.size() + sizeof(int));
        std::memcpy(buffer.data() + pointer, &soloWeapon, sizeof(int));
        pointer += sizeof(int);

        return buffer;
    }

    void Deserialize(const std::vector<uint8_t>& buffer)
    {
        size_t pointer = 0;

        std::memcpy(&uniqueID, buffer.data() + pointer, sizeof(uint32_t));
        pointer += sizeof(uint32_t);

        std::memcpy(&gameMode, buffer.data() + pointer, sizeof(int));
        pointer += sizeof(int);

        std::memcpy(&soloWeapon, buffer.data() + pointer, sizeof(int));
        pointer += sizeof(int);
    }
};