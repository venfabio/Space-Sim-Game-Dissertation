#include "TransactionMessage.h"


TransactionMessage::TransactionMessage(bool b, int id, int p, GameObject* go) 
	: Message("transaction")
{
	buy = b;
	key = id;
	price = p;
	other = go;
}


TransactionMessage::~TransactionMessage()
{
}
