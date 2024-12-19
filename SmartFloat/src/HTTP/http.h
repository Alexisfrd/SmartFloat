#ifndef HTTP_H
#define HTTP_H

#include <Arduino.h> // Ajoutez cette ligne pour définir String
/**************************************************************************** */
/*                          Prototype de fonctions                            */
/**************************************************************************** */

/** Envoie une requête POST à l'URL spécifiée avec les données JSON spécifiées
 * [IN] jdata : Données JSON à envoyer
 * [IN] url : URL de destination
 * [IN] callback : Fonction de rappel pour gérer la réponse 
 */
void POST(String jdata, String url, std::function<void(String)> callback);

/** Envoie les données du capteur au serveur
 * [IN] sensorName : Nom du capteur
 * [IN] sensorValue : Valeur du capteur
 * [IN] dateString : Date de la mesure
 * [IN] token : Jeton d'authentification
 * [IN] target : ID du capteur
 */
void sendData(String sensorName, float sensorValue, String dateString, String token, int target);

/** Gère le processus de connexion et d'envoi de données
 * [IN] sensorName : Nom du capteur
 * [IN] sensorValue : Valeur du capteur
 * [IN] dateString : Date de la mesure
 * [IN] login : Nom d'utilisateur
 * [IN] password : Mot de passe
 * [IN] target : ID du capteur
 */
void handleLoginAndSendData(String sensorName, float sensorValue, String dateString, String login, String password, int target);

/** Gère la réponse de connexion
 * [IN] response : Réponse du serveur
 */
String parseToken(String response);

/** Génère une date formatée
 * [OUT] Date formatée
 */
String getFormattedDate();

/** Gère la réponse de connexion
 * [IN] response : Réponse du serveur
 */
void handleLoginResponse(String response);

/** Gère la réponse de l'envoi de données
 * [IN] response : Réponse du serveur
 */
void handlePushDataResponse(String response);

#endif // HTTP_H