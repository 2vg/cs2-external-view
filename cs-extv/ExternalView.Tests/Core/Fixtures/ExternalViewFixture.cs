using AutoFixture;
using AutoFixture.AutoMoq;
using ExternalView.Tests.Core.Fakes;
using System.Numerics;

namespace ExternalView.Tests.Core.Fixtures
{
    internal class ExternalViewFixture
    {
        public readonly IFixture Fixture;

        public readonly FakeExternalViewCsApi Api;

        public ExternalViewFixture()
        {
            Fixture = new Fixture();

            Fixture.Customize(new AutoMoqCustomization());

            Fixture.Register(() => new Vector3(
                Fixture.Create<float>(),
                Fixture.Create<float>(),
                Fixture.Create<float>()
            ));

            Fixture.Register(() => new FakeExternalViewCsApi());
            Fixture.Register(() => new FakeExternalViewCsPlayer
            {
                HandleRaw = Fixture.Create<uint>(),
                Slot = Fixture.Create<int>(),
                Name = Fixture.Create<string>(),
                Origin = Fixture.Create<Vector3>(),
            });

            Api = Fixture.Freeze<FakeExternalViewCsApi>();
        }

        public ExternalViewFixture SetNumPlayers(int nPlayers)
        {
            Api.FakePlayers = Fixture.CreateMany<FakeExternalViewCsPlayer>(nPlayers).ToList();
            return this;
        }

        public FakeExternalViewCsPlayer? MainPlayer { get => Api.FakePlayers.FirstOrDefault(); }

        public List<FakeExternalViewCsPlayer> Players { get => Api.FakePlayers; }
    }
}
