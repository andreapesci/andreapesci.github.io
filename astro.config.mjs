// @ts-check
import { defineConfig } from 'astro/config';


// https://astro.build/config
export default defineConfig({
  output: 'static',
  site: 'https://andreapesci.com',
  trailingSlash: 'never',
  build: {
    format: 'directory',
  },
  vite: {
    ssr: {
      noExternal: ['astro-transitions'],
    },
  }
});
