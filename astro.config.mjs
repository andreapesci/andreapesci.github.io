// @ts-check
import { defineConfig } from 'astro/config';
import mdx from "@astrojs/mdx";


// https://astro.build/config
export default defineConfig({
  output: 'static',
  site: 'https://andreapesci.com',
  trailingSlash: 'never',
  integrations: [mdx()],
  build: {
    format: 'directory',
  },
  vite: {
    ssr: {
      noExternal: ['astro-transitions'],
    },
  },
  prefetch: {
    prefetchAll: true,
    defaultStrategy: 'hover'
  },
});
