using ExternalView.Tests.Core.Fakes;
using ExternalView.Tests.Core.Fixtures;
using LupercaliaMGCore.modules.ExternalView.Cameras;

namespace ExternalView.Tests.Core.Cameras
{
    public class WatchCameraTests
    {
        private readonly ExternalViewFixture _Fixture;

        public WatchCameraTests()
        {
            _Fixture = new ExternalViewFixture();
        }

        private WatchCamera CreateCamera(string? initialTarget = "", int playerIdx = 0)
        {
            var ctx = new FakeCameraContext(_Fixture.Api, _Fixture.Api.FakePlayers[playerIdx]);
            return new WatchCamera(ctx, initialTarget);
        }

        [Fact]
        public void ShouldChangeWatchTarget_AfterTargetDead()
        {
            _Fixture.SetNumPlayers(3);

            var initTarget = _Fixture.Players[1];
            var nextTarget = _Fixture.Players[2];

            var camera = CreateCamera(initTarget.Name);

            initTarget.IsAlive = false;
            initTarget.TimeElapsedFromLastDeath = 0;

            camera.Update();

            Assert.Equal(camera.CurrentTarget, initTarget);

            initTarget.TimeElapsedFromLastDeath = 10;

            camera.Update();

            Assert.NotEqual(camera.CurrentTarget, initTarget);
            Assert.Equal(camera.CurrentTarget, nextTarget);
        }

        [Fact]
        public void ShouldEndWatchTarget_AfterAllPlayersDead()
        {
            _Fixture.SetNumPlayers(2);

            var camera = CreateCamera();

            var target = _Fixture.Players[1];

            target.IsAlive = false;
            target.TimeElapsedFromLastDeath = 0;

            Assert.True(camera.Update());
            Assert.Equal(camera.CurrentTarget, target);

            target.TimeElapsedFromLastDeath = 10;

            Assert.False(camera.Update());
        }
    }
}
