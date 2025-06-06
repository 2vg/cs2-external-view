using LupercaliaMGCore.modules.ExternalView.API;
using LupercaliaMGCore.modules.ExternalView.Cameras;
using LupercaliaMGCore.modules.ExternalView.Player;

namespace ExternalView.Tests.Core.Fakes
{
    internal class FakeCameraContext : ICameraContext
    {
        public FakeExternalViewCsApi FakeApi;
        public FakeExternalViewCsPlayer FakePlayer;

        public FakeCameraContext(FakeExternalViewCsApi api, FakeExternalViewCsPlayer player)
        {
            FakeApi = api;
            FakePlayer = player;
            CameraEntity = api.CreateCameraEntity();
        }

        public IExternalViewCsApi Api { get => FakeApi; }
        public IExternalViewCsEntity? CameraEntity { get; set; }
        public IExternalViewCsPlayer Player { get => FakePlayer; }
        public PlayerConfig Config { get; set; } = new PlayerConfig();
    }
}
