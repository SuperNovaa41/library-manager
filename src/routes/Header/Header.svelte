<script lang="ts">
  import Item from "./Item.svelte";

  enum ViewMode {
    Grid,
    List,
  }

  let view_mode = ViewMode.Grid;

  function toggle_view() {
    if (view_mode == ViewMode.Grid) {
      view_mode = ViewMode.List;
    } else if (view_mode == ViewMode.List) {
      view_mode = ViewMode.Grid;
    }
  }
</script>

<nav>
  <div class="title">
    <div class="icon">󰗚</div>
    Library Manager
  </div>
  <div class="items">
    <Item></Item>
    <Item on:click={toggle_view}>
      {#if view_mode == ViewMode.Grid}
        󰕰
      {:else if view_mode == ViewMode.List}
        󰕲
      {/if}
    </Item>
    <Item></Item>
  </div>
</nav>

<style>
  nav {
    height: 80px;
    background-color: var(--dark-gray);
    display: flex;
    align-items: center;

    & div {
      height: 100%;

      padding: 0 25px;

      display: flex;
      align-items: center;

      user-select: none;
      -webkit-user-select: none;
      -ms-user-select: none;

      &:hover {
        cursor: default;
      }

      &.title {
        & .icon {
          font-family: "NFSymbols", monospace;
          padding-left: 0;
        }

        width: 100%;
        min-width: 340px;
        font-size: 40px;
        font-weight: bold;
        font-family: "Oswald", sans-serif;
      }

      &.items {
        justify-content: flex-end;
      }
    }
  }
</style>
