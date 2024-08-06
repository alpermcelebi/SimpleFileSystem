#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>

class Block{
public:
	Block(){
		content = "";
		size = 0;
	}
	Block(const std::string &content){
		this->content = content;
		size = content.size();
	}

	friend std::ostream &operator<<(std::ostream &os, const Block &obj)
    {
        os << obj.content << std::endl << obj.size;
        return os;
    }

    bool operator==(const Block &obj){
    	return content == obj.content && size == obj.size;
    }

    Block operator+(const Block& rhs) {
    
    this->content += rhs.content;
    this->size += rhs.size;
    return *this;
}

    std::string getContent() const{
    	return content;
    }

    void edit(const std::string &newContent){
    	content = newContent;
    	size = content.size();
    }

    void removeContent(){
    	content = "";
    	size = 0;
    }

    size_t getSize() const{
    	return size;
    }
private:
	std::string content;
	size_t size;
};

#endif 