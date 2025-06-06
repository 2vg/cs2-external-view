using LupercaliaMGCore.modules.ExternalView.API;
using LupercaliaMGCore.modules.ExternalView.Utils;
using System.Numerics;

namespace ExternalView.Tests.Core.Fakes
{
    internal class FakeExternalViewCsPlayer
        : FakeExternalViewCsEntity
        , IExternalViewCsPlayer
    {
        public int Slot { get; set; } = -1;

        public string Name { get; set; } = "";
        public bool IsAdmin { get; set; } = false;
        public bool IsAlive { get; set; } = true;
        public bool IsSpectator { get; set; } = false;
        public bool IsInWater { get; set; } = false;
        public float TimeElapsedFromLastDeath { get; set; } = 0;
        public Vector3 ViewAngle { get; set; } = Vector3.Zero;
        public ButtonState Buttons { get; set; } = new ButtonState();

        public IExternalViewCsEntity? ViewEntity { get; set; } = null;

        public bool IsMovable { get; set; } = true;
        public bool IsWeaponPickupEnabled { get; set; } = true;
        public IExternalViewCsWeapon? ActiveWeapon { get; set; } = null;

        public void UpdateButtonState()
        {
        }

        public void PrintToChat(string message, params object[] args)
        {
        }
    }
}
