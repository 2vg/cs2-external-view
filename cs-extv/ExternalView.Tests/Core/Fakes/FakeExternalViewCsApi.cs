using LupercaliaMGCore.modules.ExternalView.API;

namespace ExternalView.Tests.Core.Fakes
{
    internal class FakeExternalViewCsApi : IExternalViewCsApi
    {
        public FakeExternalViewConVars FakeConVars = new FakeExternalViewConVars();
        public List<FakeExternalViewCsPlayer> FakePlayers = new();

        public float DeltaTime { get; set; } = 1.0f / 64;
        public float CurrentTime { get; set; } = 0;
        public IExternalViewConVars ConVars { get => FakeConVars; }

        public IEnumerable<IExternalViewCsPlayer> AllPlayers { get => FakePlayers; }

        public IExternalViewCsPlayer? GetPlayer(ulong id)
        {
            return FakePlayers.Find(player => player.HandleRaw == id);
        }

        public IExternalViewCsPlayer? GetPlayerBySlot(int slot)
        {
            return FakePlayers.Find(player => player.Slot == slot);
        }

        public IExternalViewCsEntity? CreateCameraEntity()
        {
            return new FakeExternalViewCsEntity();
        }

        public IExternalViewCsEntity? CreatePreviewModelEntity(IExternalViewCsPlayer player)
        {
            return new FakeExternalViewCsEntity();
        }
    }
}
