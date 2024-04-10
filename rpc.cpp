#include "discord_rpc.h" // Include the Discord Rich Presence library

void UpdateRichPresence(int playerCount, const char* location, const char* mode) {
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = location; // Set the location as the "state"
    discordPresence.details = mode; // Show whether in Online or Story mode
    discordPresence.largeImageKey = "image_1_";
    discordPresence.partySize = playerCount;
    discordPresence.partyMax = 32; // Assuming max session size is 32
    Discord_UpdatePresence(&discordPresence); // Update the presence
}

void UpdateDiscordPresence() {
    int playerCount = NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();  // Get player count
    const char* location = "Los Santos"; // Replace with actual location

    // Determine the game mode
    bool isInOnlineMode = NETWORK::NETWORK_IS_SESSION_STARTED();
    const char* mode = isInOnlineMode ? "Online Mode" : "Story Mode";

    UpdateRichPresence(playerCount, location, mode);
}

void MainLoop() {
    while (true) {
        UpdateDiscordPresence();
        Sleep(10000); // Update every 10 seconds
    }
}

int main() {
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize("941965788666019890", &handlers, 1, NULL);

    MainLoop();

    Discord_Shutdown();
    return 0;
}
