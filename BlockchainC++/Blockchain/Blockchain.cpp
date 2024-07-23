#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <string>

class Block {
public:
    int index;
    std::string previous_hash;
    long timestamp;
    std::string data;
    std::string hash;

    Block(int idx, std::string prev_hash, long time, std::string d, std::string h)
        : index(idx), previous_hash(prev_hash), timestamp(time), data(d), hash(h) {}
};

// Fonction pour calculer un hash simplifié
std::string calculate_hash(int index, std::string previous_hash, long timestamp, std::string data) {
    std::stringstream ss;
    ss << index << previous_hash << timestamp << data;
    return std::to_string(std::hash<std::string>{}(ss.str()));
}

// Fonction pour créer le bloc genesis
Block create_genesis_block() {
    long timestamp = std::time(nullptr);
    std::string genesis_hash = calculate_hash(0, "0", timestamp, "Genesis Block");
    return Block(0, "0", timestamp, "Genesis Block", genesis_hash);
}

// Fonction pour créer un nouveau bloc
Block create_new_block(Block previous_block, std::string data) {
    int index = previous_block.index + 1;
    long timestamp = std::time(nullptr);
    std::string previous_hash = previous_block.hash;
    std::string hash = calculate_hash(index, previous_hash, timestamp, data);
    return Block(index, previous_hash, timestamp, data, hash);
}

int main() {
    // Créer la blockchain et ajouter le bloc Genesis
    std::vector<Block> blockchain;
    Block genesis_block = create_genesis_block();
    blockchain.push_back(genesis_block);

    // les détails du bloc Genesis
    std::cout << "Le Block #" << genesis_block.index << " (Genesis) a ete ajoute a la blockchain" << std::endl;
    std::cout << "Hash: " << genesis_block.hash << std::endl;
    std::cout << "Previous Hash: " << genesis_block.previous_hash << std::endl << std::endl;

    // Pour Ajouter quelques blocs à la blockchain
    int num_of_blocks_to_add = 5;
    Block previous_block = blockchain.back();

    for (int i = 0; i < num_of_blocks_to_add; ++i) {
        std::string new_block_data = "Block " + std::to_string(i + 1) + " Data";
        Block new_block = create_new_block(previous_block, new_block_data);
        blockchain.push_back(new_block);

        std::cout << "Le Block #" << new_block.index << " a ete ajoute a la blockchain" << std::endl;
        std::cout << "Hash: " << new_block.hash << std::endl;
        std::cout << "Previous Hash: " << previous_block.hash << std::endl << std::endl;

        previous_block = new_block;
    }

    return 0;
}
