#include "File.h"

Block File::getBlock(int index) const
{
    Block empty;
	if(blocks.getNodeAtIndex(index) == NULL) return empty;
	
	Block ret = (blocks.getNodeAtIndex(index))->data;
	return ret;
	
}

size_t File::fileSize() const
{
	size_t totalSize = 0;
    for (int i = 0; i < blocks.getSize(); i++) {
        totalSize += blocks.getNodeAtIndex(i)->data.getSize();
    }
    return totalSize;

}

int File::numBlocks() const
{
	return blocks.getSize();
}

bool File::isEmpty() const
{
	return blocks.isEmpty();
}

bool File::operator==(const File &rhs) const
{
	if (blocks.getSize() != rhs.blocks.getSize()) {
        return false; 
    }
        
    for (int i = 0; i < blocks.getSize(); i++) {
        if (blocks.getNodeAtIndex(i)->data.getContent() != rhs.blocks.getNodeAtIndex(i)->data.getContent()) {
            return false; 
        }
    }
        
    return true;
}

void File::newBlock(const Block &block)
{
	blocks.append(block);
}

void File::removeBlock(int index)
{
	if (index >= 0 && index < blocks.getSize()) {
        blocks.removeNodeAtIndex(index);
        }
}

void File::mergeBlocks(int sourceIndex, int destIndex)
{
	blocks.mergeNodes(sourceIndex, destIndex);
}

void File::printContents() const{
	if(isEmpty()){
		std::cout << "File is empty" << std::endl;
	}
	else{
		for(int i = 0; i < blocks.getSize(); i++){
			Node<Block> *block = blocks.getNodeAtIndex(i);
			std::cout << block->data.getContent();
		}
		std::cout << std::endl << fileSize() << std::endl;
	}
}