using LupercaliaMGCore.modules.ExternalView.API;

namespace ExternalView.Tests.Core.Fakes
{
    internal class FakeExternalViewCsWeapon : IExternalViewCsWeapon
    {
        private uint HandleRaw;

        public FakeExternalViewCsWeapon(uint handleRaw)
        {
            HandleRaw = handleRaw;
        }

        public bool IsValid { get; set; } = true;
        public bool CanAttack { get; set; } = true;

        public bool Equals(IExternalViewCsWeapon? other)
        {
            var otherWeapon = other as FakeExternalViewCsWeapon;

            if (otherWeapon == null)
                return false;

            return HandleRaw == otherWeapon.HandleRaw;
        }
    }
}
