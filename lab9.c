#include <stdio.h>

// RecordType
struct RecordType
{
	int		id; //key
	char	name; //value
	int		order; 
};

struct Node{
	struct RecordType* data;
	struct RecordType* next;
};

struct HashType
{
	int num;
	int capacity;
	struct Node** arr;
};

void setNode(struct Node* node, struct RecordType* data)
{
	node->data = data;
	node->next = NULL;
	return;
}

void initializeHashMap(struct HashType* map)
{
	map->capacity = 100;
	map->num = 0;
	map->arr = (struct Node**)malloc(sizeof(struct Node*)*map->capacity);
}


int hashFunction(struct HashType* map, struct RecordType* data)
{
	int bucket;
	int sum = 0;
	int factor = 31;
	
	int key = data->id;
	while(key > 0)
	{
		sum = ((sum % map->capacity) + ((key % 10) * factor) % map->capacity) % map->capacity;
		factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__) % __INT16_MAX__);
		key /= 10;
	}
	
	bucket = sum;
	return bucket;
}


void insert(struct HashType* map, struct RecordType** ppData, int size)
{
	int i;
	struct RecordType *data;
	for(i = 0; i < size; i++)
	{
		data = *ppData + i;
	
		int bucket = hashFunction(map, data);
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		
		setNode(newNode, data);
		
		if(map->arr[bucket] == NULL) 
		{
			map->arr[bucket] = newNode;
		}
		else
		{
			newNode->next = map->arr[bucket];
			map->arr[bucket] = newNode;
		}
		
		printf("%d\n", data->id);
	}

	return;
}


// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;
	for (i=0;i<100;++i)
	{
		if(pHashArray->arr != NULL)
		{
			//printf("%d\n", pHashArray->arr[i]->data->id);
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	
	// Your hash implementation
	struct HashType* map = (struct HashType*)malloc(sizeof(struct HashType));
	initializeHashMap(map);
	insert(map, &pRecords, recordSz);
	displayRecordsInHash(map, recordSz);
	
	return 0;	
}
