using CounterStrikeSharp.API;
using LupercaliaMGCore.modules.ExternalView.Utils;

namespace LupercaliaMGCore.Tests.modules.ExternalView.Utils
{
    public class ButtonStateTests
    {
        [Fact]
        public void ShouldReturnIfButtonsAreDown()
        {
            var state = new ButtonState();

            state.Update(
                PlayerButtons.Attack |
                PlayerButtons.Jump
            );

            Assert.True(state.IsDown(PlayerButtons.Attack));
            Assert.True(state.IsDown(PlayerButtons.Jump));
            Assert.False(state.IsDown(PlayerButtons.Forward));
            Assert.False(state.IsDown(PlayerButtons.Duck));
        }

        [Fact]
        public void ShouldReturnIfButtonsArePressed()
        {
            var state = new ButtonState();

            // Frame #1
            state.Update(
                PlayerButtons.Attack |
                PlayerButtons.Jump
            );

            // Frame #2
            // - Holds Attack
            // - Releases Jump
            // - Presses Forward
            // - Presses Duck
            state.Update(
                PlayerButtons.Attack |
                PlayerButtons.Forward |
                PlayerButtons.Duck
            );

            Assert.False(state.IsPressed(PlayerButtons.Attack));
            Assert.False(state.IsPressed(PlayerButtons.Jump));
            Assert.True(state.IsPressed(PlayerButtons.Forward));
            Assert.True(state.IsPressed(PlayerButtons.Duck));
        }
    }
}
