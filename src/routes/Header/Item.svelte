<button>
  <slot />
</button>

<style>
  button {
    font-family: "NFSymbols", monospace;
    font-size: 20px;
    color: var(--foreground);

    padding: 0 10px;
    margin: 0 10px;
    border-radius: 50%;

    display: flex;
    justify-content: center;
    align-items: center;

    background: transparent;
    border: none;

    aspect-ratio: 1;

    transition: background-color 0.1s linear, text-shadow 0.1s linear;

    &:hover {
      cursor: pointer;
      background-color: var(--light-gray);
      text-shadow: 2px 2px var(--dark-gray);
    }

    &:last-child {
      margin-right: 0;
    }
  }
</style>
