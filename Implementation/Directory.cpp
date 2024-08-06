#include "Directory.h"

File Directory::getFile(int index) const
{
    File a;
	if(index < 0 || index >= (int)numFiles()) return a;
	return files[index];
}

size_t Directory::directorySize() const
{
	if(isEmpty()) return 0;
	int i, count = numFiles();
    size_t dir_size = 0;
    for(i = 0; i < numFiles(); i++) {
        dir_size = dir_size + files[i].fileSize();
    }
    return dir_size;
}

bool Directory::isEmpty() const
{
	return numFiles() == 0;
}

size_t Directory::numFiles() const
{
	return files.size();
}

void Directory::newFile(const File &file)
{
	files.push_back(file);
}

void Directory::removeFile(int index)
{   
    if(index < 0 || index >= numFiles()) return;
	files.erase(files.begin()+index);
	return;
}

void Directory::removeFile(File &file)
{
	int i, count = numFiles();
	for(i = 0; i < count; i++) {
	    if(files[i] == file) {
	        removeFile(i);
	        return;
	    }
	}
	return;
}

void Directory::removeBiggestFile()
{
	int i, b_fileIndex = 0;
	for(i = 1; i < numFiles(); i++) {
	    if(files[i].fileSize() > files[i-1].fileSize()) {
	        b_fileIndex = i;
	    }
	}
	removeFile(b_fileIndex);
}
