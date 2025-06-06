using LupercaliaMGCore.modules.ExternalView.API;
using System.Numerics;

namespace ExternalView.Tests.Core.Fakes
{
    internal class FakeExternalViewCsEntity : IExternalViewCsEntity
    {
        public bool IsValid { get; set; } = true;
        public uint HandleRaw { get; set; } = 0;
        public Vector3 Origin { get; set; } = Vector3.Zero;
        public Vector3 Rotation { get; set; } = Vector3.Zero;
        public Vector3 Velocity { get; set; } = Vector3.Zero;

        public void Teleport(Vector3? origin, Vector3? angle, Vector3? velocity)
        {
            if (origin.HasValue)
            {
                Origin = origin.Value;
            }

            if (angle.HasValue)
            {
                Rotation = angle.Value;
            }

            if (velocity.HasValue)
            {
                Velocity = velocity.Value;
            }
        }

        public void Remove()
        {
            IsValid = false;
        }

        public bool IsVisible { get; set; } = true;

        public IExternalViewCsEntity? Parent { get; set; }
        public string Model { get; set; } = "";

        public bool Equals(IExternalViewCsEntity? other)
        {
            var otherEntity = other as FakeExternalViewCsEntity;

            if (otherEntity == null)
                return false;

            return HandleRaw == otherEntity.HandleRaw;
        }
    }
}
