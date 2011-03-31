/*
* Author: Jarryd Hall
* Purpose: An XML Parser to parse a tilemap
* Note: The TMX file has been converted to an xml file before hand
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

xmlXPathObjectPtr retrieveXmlnodeset (xmlDocPtr doc, xmlChar *xpath)
{
	xmlXPathContextPtr context;
	xmlXPathObjectPtr object;

	context = xmlXPathNewContext(doc);
	if (context == NULL) 
	{
		printf("xmlXPathNewContext error\n");
		return NULL;
	}
	object = xmlXPathEvalExpression(xpath, context);
	xmlXPathFreeContext(context);
	
	if (object == NULL) 
	{
		printf("xmlXPathEvalExpression error\n");
		return NULL;
	}
	if (xmlXPathNodeSetIsEmpty(object->nodesetval))
	{
		xmlXPathFreeObject(object);
		printf("xmlXPathObject couldnt be created\n");
		return NULL;
	}
	return object;
}

void getMapDetails (xmlDocPtr doc, xmlNodePtr cur)
{
	char *array[4];
	xmlChar *mapWidth;
	xmlChar *mapHeight;
	xmlChar *tileWidth;
	xmlChar *tileHeight;
	
	if((!xmlStrcmp(cur->name, (const xmlChar *)"map")))
	{
		mapWidth = xmlGetProp(cur, "width");
		array[0] = (char *)mapWidth;
		printf("map width is %s\n", array[0]);
		mapHeight = xmlGetProp(cur, "height");
		array[1] = (char *)mapHeight;
		printf("map height is %s\n", array[1]);
		tileWidth = xmlGetProp(cur, "tilewidth");
		array[2] = (char *)tileWidth;
		printf("tile width is %s\n", array[2]);
		tileHeight = xmlGetProp(cur, "tileheight");
		array[3] = (char *)tileHeight;
		printf("tile height is %s\n", array[3]);
	}
}

// A function to return all the tiles and their type. 
// e.g. background tiles and collision tiles
// purpose: Outputs the list of tiles and their types which will be used 
// to create a 2dimensional array representation
// TODO: add code to create the 2d array representation on the fly

void getTileDetails (xmlDocPtr doc, xmlNodePtr cur)
{
	xmlChar *xpath = (xmlChar*) "//layer[@name=\"collision\"]/data/tile/@gid";
	xmlNodeSetPtr nodeset;
	xmlXPathObjectPtr result;

	xmlChar *keyword;

	int i;
	int numMovableTiles = 0;
	int numCollisionTiles = 0;
	int totalTiles = 0;
	
	result = retrieveXmlnodeset (doc, xpath);
	if (result) 
	{
		nodeset = result->nodesetval;
		for (i=0; i < nodeset->nodeNr; i++) 
		{
			keyword = xmlNodeListGetString(doc, nodeset->nodeTab[i]->xmlChildrenNode, 1);
		
			int id = atoi(keyword);
			int index = i;
			
			if (id == 0)
			{
				numMovableTiles += 1;
				printf("Movable tile id: %d for index: %d\n", id, index);
			}
			if (id == 121)
			{
				numCollisionTiles += 1;			
				printf("Collision tile id : %d for index: %d\n", id, index);
			}
			 		
			xmlFree(keyword);
		}
		xmlXPathFreeObject (result);
	}
	
	totalTiles = numMovableTiles + numCollisionTiles;
	
	printf("number of collision tiles : %d\n", numCollisionTiles);
	printf("number of movable tiles : %d\n", numMovableTiles);
	printf("Total tiles : %d\n", totalTiles);
}

// Helper function to retrieve a the value for the specfied attribute at a specified node

char* getAttributeValueForNode (xmlDocPtr doc, xmlNodePtr cur, char *node, char *attribute)
{
	xmlChar *attributeValue;
	cur = cur->xmlChildrenNode;
	
	while (cur != NULL)
	{
		if((!xmlStrcmp(cur->name, (const xmlChar *) node)))
		{
			attributeValue = xmlGetProp(cur, attribute);
			printf("node: %s value: %s\n", node, attributeValue);
		}
		cur = cur->next;
	}
	//xmlFree(attributeValue);
	return (char *)attributeValue;
}

void parseDoc(char *docname) 
{
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(docname);
	
	if (doc == NULL) 
	{
		fprintf(stderr,"Parsing was unsuccesful \n");
		return;
	}
	cur = xmlDocGetRootElement(doc);
	
	if (cur == NULL) 
	{
		fprintf(stderr,"No XML Data\n");
		xmlFreeDoc(doc);
		return;
	}
	if (xmlStrcmp(cur->name, (const xmlChar *) "map"))
	{
		fprintf(stderr,"Root node != map, not a tmx file");
		xmlFreeDoc(doc);
		return;
	}
	
	getMapDetails(doc, cur);
	getTileDetails(doc, cur);

	xmlFreeDoc(doc);
	return;
}

int main(int argc, char **argv) 
{
	char *docname;

	if (argc <= 1) 
	{
		printf("Usage: %s docname\n", argv[0]);
		return(0);
	}

	docname = argv[1];
	parseDoc (docname);
	
	return (1);
}